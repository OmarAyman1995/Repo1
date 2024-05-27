# OBDAddon
OBD Addon gateway 

This is Omar Ayman development branch




  * ------------------Author Notes--------------------
  *
  * ______________________1________________________
  * this is just a test code for SD card and FILE32 system
  * please format SD card first before anything
  * then use this code to create 20 files at ones
  *
  *_______________________2_________________________
  *
  *do NOT forget to call ---vid_initSD()--- before using fileHandle.c APIs
  *...(until now it is just 1 API which is enum_createNewSdCardFile)
  _______________________3_________________________
*
*use ----enum_createNewSdCardFile()----- API to create files
*________________________4__________________________
*you should not exceed (11 chars at total)
* for example : follow this when you choose the name : u8_t NewFileName[11] = {"CREW1   TXT"};
*_______________________5___________________________
* the extension of the file Should be TXT, otherwise the result is not tested