/* 0: left RGB
 * 1: right RGB
 * 2: shelf
 */
#define TYPE 0

#if TYPE != 2
# define AO_RED   D5
# define AO_GREEN D6
# define AO_BLUE  D7
#endif

#if TYPE == 2
# define AO_SHELF D8
#endif
