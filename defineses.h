#define VOLTAGE 0x00
#define CURRENT 0x06
#define ACT_POWER 0x0C
#define APPARENT_POWER 0x12
#define REACT_POWER 0x18
#define POWER_FACTOR 0x1E
#define FREQ 0x46
#define IMP_ACT_ENERGY 0x48
#define EXP_ACT_ENERGY 0x4A
#define IMP_REACT_ENERGY 0x4C
#define EXP_REACT_ENERGY 0x4E
#define TOTAL_ACT_ENERGY 0x156
#define TOTAL_REACT_ENERGY 0x158

static int registers[] = {0x00, 0x06, 0x0C, 0x12, 0x18, 0x1E, 0x46, 0x48, 0x4A, 0x4C, 0x4E, 0x156, 0x158};

static char *legend[] = {
	"Voltage",
	"Current",
	"Active power",
	"Apparent power",
	"Reactive power",
	"Power factor",
	"Frequency",
	"Import act energy",
	"Export act energy",
	"Import react energy",
	"Export react energy",
	"Total act energy",
	"Total react energy",
};
