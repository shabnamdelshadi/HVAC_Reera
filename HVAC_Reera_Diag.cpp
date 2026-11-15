#include "HVAC_Reera_Diag.h"//Delshadi
#include "MSG_HVAC_Reera_Diag.h"
#include "ArrayTools.h"
#include "OtherHeader\HVAC_Reera_Diag_OH.h"
#include "UsefulMethods.h"

HVAC_Reera_Diag::HVAC_Reera_Diag(void)
{
}
HVAC_Reera_Diag::~HVAC_Reera_Diag(void)
{
}
bool HVAC_Reera_Diag::Configuration(CommandAdorner* Command)
{	OBDii.Security_Pass(Command, 1);
	byte response[25] = {};
	const uint8_t number_of_variable = 1; 
	while (Manager.BreakFlag == false)
	{
		for (byte i =2; i < Command->DB->LengthOfSendingFrames; i++)
		{
			CommandAdorner::SendingFrame_ByteArrayFrame_structure* sendFrame = Command_SendingFrames(Command, i);

			if ((OBDii.Send_Receive(sendFrame->Lengh, sendFrame->ByteFrame, response, sizeof(response)) == null) || (response[0] == 0x7F))
				MarkInvalidVariablesAndSetBody(Command, sendFrame->ExpectingBodyLength, 2);
			else
				BodyConcat(Command, response, sendFrame->ExpectingBodyLength);
		}
		ShowVar var[number_of_variable + 1];
		Setvariables(Command, var, number_of_variable);
		if (!OnGetVariablesData(Command, var))
		{
			if (Manager.BreakFlag)
			{
				Manager.BreakFlag = false;
				Restart();
				return false;
			}
			else
				continue;
		}
		for (u8 i = 0; i < number_of_variable; i++)
		{
			if (!var[i].State.IsChanged)
				continue;
			var[i].State.IsChanged = false;
			CommandAdorner::SendingFrame_ByteArrayFrame_structure* sendFrame = Command_SendingFrames(Command, i+2);
			byte send_buff[20] = { 0x2E, 0xF1,0x90};
			switch (i)
			{
			case 0:     // VIN
    			memcpy(send_buff + 3,(byte*)var[i].Value,Command->Variables[i]->DB->Length);
    			break;
			}
			if ((OBDii.Send_Receive(sizeof(send_buff), send_buff, response, sizeof(response)) == NULL) || (response[0] == 0x7F))
			return false;
			Restart();
		}
	}
	 return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HVAC_Reera_Diag::Date_Configuration(CommandAdorner* Command)
{
 OBDii.Security_Pass(Command, 1);
 byte response[10] = {};
	const uint8_t number_of_variable = 3; 

	while (1)
	{
		for (byte i = 2; i < Command->DB->LengthOfSendingFrames; i++)
		{
			CommandAdorner::SendingFrame_ByteArrayFrame_structure* sendFrame = Command_SendingFrames(Command, i);

			if ((OBDii.Send_Receive(sendFrame->Lengh, sendFrame->ByteFrame, response, sizeof(response)) == null) || (response[0] == 0x7F))
				MarkInvalidVariablesAndSetBody(Command, sendFrame->ExpectingBodyLength, 2);
			else
				BodyConcat(Command, response, sendFrame->ExpectingBodyLength);
		}
		ShowVar var[number_of_variable + 1];
		Setvariables(Command, var, number_of_variable);
		u8 Selected_Item = OnGetVariablesData(Command, var, Return_SelectedInx);
		if (Manager.BreakFlag == true)
		{
			Manager.BreakFlag = false;
			return false;
		}
		CommandAdorner::SendingFrame_ByteArrayFrame_structure* sendFrame = Command_SendingFrames(Command, Selected_Item);
		byte send_buff[5] = { 0x2E, sendFrame->ByteFrame[1]};
		switch (Selected_Item)
		{
		case 0:   
		case 1:   
		case 2:   
		
		{
			u8 time [5] = {};
			UsefulMethods::DateTime_Now(time);//yyMMddHHmm
			for(u8 i=0; i<3; i++)
			{
				time[i] = (time[i] / 10) * 16 + (time[i] % 10);
			}
			u16 year = 0x2000 + time[0];
			GetDateDataDialog_Hex(Messages(HVAC_Reera_Diag_EnterDate), &year, &time[1], &time[2], true);
			
			if (Manager.BreakFlag)
			{
				Manager.BreakFlag = false;
				continue;
			}
			time[0] = time[2];
			time[2] = (u8)year;
			memcpy(send_buff + 2,time,Command->Variables[Selected_Item]->DB->Length);
		}
		break;
		default:
			break;
		}
		if ((OBDii.Send_Receive(sizeof(send_buff), send_buff, response, sizeof(response)) == NULL) || (response[0] == 0x7F))
		{
			OnShowMessage_Messages(HVAC_Reera_Diag_OperationFailed, None, false);	
		}
		Sleep(500);
		Restart();
	}
}
	