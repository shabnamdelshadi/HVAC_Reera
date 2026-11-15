#ifndef __HVAC_REERA_DIAG_H
#define __HVAC_REERA_DIAG_H

#include "rayanmessage.h"
#include "Algorithm.h"

class HVAC_Reera_Diag : public BaseAlgorithm
{
public:
	virtual bool InternalSwitchCase(CommandAdorner* Command);
	const static u16 Class_ID;
	HVAC_Reera_Diag(void);
	~HVAC_Reera_Diag(void);

	bool Configuration(CommandAdorner* Command);
  bool Date_Configuration(CommandAdorner* Command);
	bool Remote_Learning(CommandAdorner* Command);
	bool ResetOdometer(CommandAdorner* Command);

private:
	
};
#endif //__HVAC_Reera_Diag_H
