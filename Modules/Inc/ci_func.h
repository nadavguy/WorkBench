#include <stdint.h>
#include "cmd_interp.h"

extern bool isReportParametersActive;

extern eCI_RESULT func_vibrations(void);
extern eCI_RESULT func_vibrationRelevantAxis(void);
extern eCI_RESULT func_dir(void);
extern eCI_RESULT func_fmt(void);
extern eCI_RESULT func_activeSensors(void);
extern eCI_RESULT func_setLoadedConfigurationStatus(void);
extern uint8_t funcTable( char* token );
