#include <stdint.h>
#include "cmd_interp.h"

extern bool isReportParametersActive;
extern bool isInfwUpdateMode;

extern eCI_RESULT func_debug(void);
extern eCI_RESULT func_updateRCVersion(void);
extern eCI_RESULT func_versionReport(void);
extern eCI_RESULT func_resetRC(void);
extern eCI_RESULT func_showAvailableCommands(void);
extern eCI_RESULT func_endUpdatePhase(void);
extern eCI_RESULT func_dir(void);
extern eCI_RESULT func_fmt(void);

extern uint8_t funcTable( char* token );
