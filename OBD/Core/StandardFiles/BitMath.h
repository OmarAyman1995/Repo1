/**
 * @brief set a particular bit in a variable to 1
 * 
 */
#define SET_BIT(VAR,BIT_NO) (VAR |= 1UL<<BIT_NO)
#define CREW_SET_BIT(VAR,BIT_NO) (VAR |= 1UL<<BIT_NO)

/**
 * @brief clear a particular bit in a variable to 0
 * 
 */
#define CLR_BIT(VAR,BIT_NO) (VAR &= ~(1UL<<BIT_NO))
#define CREW_CLR_BIT(VAR,BIT_NO) (VAR &= ~(1UL<<BIT_NO))

/**
 * @brief toggle a particular bit in a variable
 * 
 */
#define TOGGLE_BIT(VAR,BIT_NO) (VAR ^= (1UL<<BIT_NO))
#define CREW_TOGGLE_BIT(VAR,BIT_NO) (VAR ^= (1UL<<BIT_NO))

/**
 * @brief extract the value of a particular bit in a variable
 * 
 */
#define GET_BIT(VAR,BIT_NO)  ((VAR>>BIT_NO) & 0x01UL)   
#define CREW_GET_BIT(VAR,BIT_NO)  ((VAR>>BIT_NO) & 0x01UL)   