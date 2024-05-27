import subprocess
import serial
import serial.tools.list_ports
import bluetooth
import time
import json
import threading
import queue

ser:serial.Serial = None
serialLock:bool = False
threadClose:bool = False
QueueOfMessages = queue.Queue()


def ConnectToBluetooth():
    global ser
    returnValue = False
    deviceCOM:str = ''
    deviceAddress:str = ''

    # # Search on a bluetooth device named 'CrewCopilot'
    # nearbyDevices = bluetooth.discover_devices(lookup_names=True)
    # for address,name in nearbyDevices:
    #     if "CrewCopilot" == name:
    #         deviceAddress = address.replace(":","")
    #         print(deviceAddress)
    #         break
    # print(nearbyDevices)

    # # Search on the COM PORT that has the same address as deviceAddress
    # if deviceAddress != '':
    #     for port in serial.tools.list_ports.comports():
    #         print(port.name + " " + port.hwid)
    #         if deviceAddress in port.hwid:
    #             deviceCOM = port.name
    #             break

    # print(deviceCOM)
    # Connect the founded COM

    try:
        ser = serial.Serial("/dev/rfcomm0", baudrate=38400, timeout=5)
        returnValue = ser.is_open
    except:
        returnValue = False

    time.sleep(5) #some time to connect with HC 05
    return returnValue






def SerialListenerThread(ser:serial.Serial):
    global serialLock
    while True:
        if serialLock == False:
            serialLock = True
            receivedData:bytes = ser.read_until(b"\r\n",1000)
            receivedDataString:str = ''
            if receivedData:
                receivedDataString = receivedData.decode()
                if threadClose == False:
                    print(receivedDataString)
                QueueOfMessages.put(receivedDataString)
            serialLock = False
            
        if threadClose == True:
            break


def SearchInQueue(search_string):
    found = False
    sizeOfQueue = QueueOfMessages.qsize()
    while sizeOfQueue != 0:
        data = QueueOfMessages.get()
        if search_string in data:
            found = True
        # Put the data back into the queue after processing
        QueueOfMessages.put(data)
        sizeOfQueue -= 1

    return found


def SendDataToBluetooth(stringData:str):
    global ser
    global serialLock

    timeout:int = 0
    while (serialLock != False) and (timeout <= 10000):
        time.sleep(0.0001)
        timeout += 1
    
    serialLock = True
    bytesData = bytes.fromhex(stringData)
    ser.write(bytesData)
    serialLock = False


def FlashCode():
    binFilePath = "/crewteq-build/TestingScript/OBD_Project.bin"
    flashAddress = "0x8000000"
    runResult = subprocess.run(["st-flash","write",binFilePath,flashAddress],stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # one more trial to flash the code if first trial failed
    if runResult.returncode != 0:
        runResult = subprocess.run(["st-flash","write",binFilePath,flashAddress],stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    return runResult.returncode == 0


if __name__ == "__main__":
    flashResult:bool = False
    connectResult:bool = False
    requestResult:bool = False
    expectedManualServiceResponse:str = '255\r\n'
    expectedDynamicServiceResponse:str = '{"3":"1","4":"100.0","5":"215","14":"63.500","12":"16383.750","13":"255","15":"215","17":"100.0","31":"65535","47":"100.0","49":"65535","66":"65.535","67":"39.215","80":"2550","51":"255","103":"215","6":"99.218","108":"-1"}\r\n'
    expectedStaticServiceResponse:str = '{"VIN":"I\x02\x01VSSZZZNHZH1008844\x01","0":"A=255 B=255 C=255 D=255","19":"255","28":"255","29":"255","30":"255","32":"A=255 B=255 C=255 D=255","64":"A=255 B=255 C=255 D=255","81":"255","95":"255","96":"A=255 B=255 C=255 D=255","99":"65535","128":"A=255 B=255 C=255 D=255","144":"-1","145":"-1","147":"-1","160":"A=255 B=255 C=255 D=255","169":"-1","192":"A=255 B=255 C=255 D=255"}\r\n'
    expectedMonitoringMessgeResponse:str = '{"203":2.96,"204":1,"205":1.09,"206":1,"207":0.00,"208":4,"209":39.66,"210":2,"211":1,"212":0}\r\n'
    
    # Start script
    print("Flashing...")
    flashResult = FlashCode()
    print("Flash code result: ", flashResult)

    if(flashResult == True):
        print("Connecting to bluetooth...")
        connectResult = ConnectToBluetooth()
        print("Connect to bluetooth result: ", connectResult)
        if(connectResult == True):
            print("Received messages from vehicle:")
            serial_thread = threading.Thread(target=SerialListenerThread, args=(ser,), daemon=True)
            serial_thread.start()
            # test manual request
            
            SendDataToBluetooth("A1 01 0D FF")
            SendDataToBluetooth("A2 FF")
            SendDataToBluetooth("A3 FF")

            time.sleep(5)

            if SearchInQueue(expectedManualServiceResponse) == True:
                print("Manual Service has successed")
                requestResult = True
            else:
                print("Manual Service has failed")
                requestResult = False
                
            # test dynamic request
            if SearchInQueue(expectedDynamicServiceResponse):
                print("Dynamic Service has successed")
                requestResult = True
            else:
                print("Dynamic Service has failed")
                requestResult = False

            # test static request
            if SearchInQueue(expectedStaticServiceResponse):
                print("Static Service has successed")
                requestResult = True
            else:
                print("Static Service has failed")
                requestResult = False

            # close thread and serial channel
            threadClose = True
            serial_thread.join(timeout=1)
            ser.close()

            if requestResult == False:
                exit(1)
        else:
            exit(1)
    else:
        exit(1)
    