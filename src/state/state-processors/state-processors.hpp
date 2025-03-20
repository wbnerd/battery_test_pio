#ifndef STATE_PROCESSORS_HPP
#define STATE_PROCESSORS_HPP

#include "../state-processor.struct.hpp"

StateProcessor* StartStateProcessor();
StateProcessor* WifiSetupStateProcessor();
StateProcessor* GpioSetupStateProcessor();
StateProcessor* OledSetupStateProcessor();
StateProcessor* InaSetupStateProcessor();
StateProcessor* BatteryCheckStateProcessor();
StateProcessor* BatteryRequestStateProcessor();
StateProcessor* BatteryErrorStateProcessor();
StateProcessor* ResistorCheckStateProcessor();
StateProcessor* ResistorRequestStateProcessor();
StateProcessor* ResistorErrorStateProcessor();
StateProcessor* ReadyForTestStateProcessor();
StateProcessor* TestStateProcessor();
StateProcessor* TestErrorStateProcessor();
StateProcessor* TestEndStateProcessor();
StateProcessor* TestResultStateProcessor();
StateProcessor* StateMachineErrorStateProcessor();
StateProcessor* InaNotFoundStateProcessor();


#endif // STATE_PROCESSORS_HPP