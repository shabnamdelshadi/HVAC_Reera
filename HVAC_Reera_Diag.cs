using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using USILogicLayer.Protocol;
using Extensions.ByteArrayExtensions;
using DataAccessLayer;
using System.Threading;
using System.IO;
using Extensions.Loggers;
using USILogicLayer.Algorithms.Algorithm_Forms;
using System.Diagnostics;
using USILogicLayer.Algorithms;


namespace USILogicLayer.Algorithms
{
    public class HVAC_Reera_Diag : Algorithm
    {
        public HVAC_Reera_Diag(RayanDataModelDataSet.ECURow ECU, LogicManager logicManager)
                                                                            : base(ECU, logicManager)
        {
            Messages["HVAC_Reera_Diag_Canceled", Language.English] = "Operation canceled by user.";
            Messages["HVAC_Reera_Diag_Canceled", Language.Farsi] = "عملیات توسط کاربر لغو شد";

            Messages["HVAC_Reera_Diag_EnterDate", Language.English] = " EnterDate ";
            Messages["HVAC_Reera_Diag_EnterDate", Language.Farsi] = " تاریخ را وارد کنید ";

            Messages["HVAC_Reera_Diag_ECU_done", Language.English] = " Operation done ";
            Messages["HVAC_Reera_Diag_ECU_done", Language.Farsi] = " مقادیر وارد شده به درستی ثبت شد ";

            Messages["HVAC_Reera_Diag_OperationFailed", Language.English] = " Operation failed! ";
            Messages["HVAC_Reera_Diag_OperationFailed", Language.Farsi] = " عملیات با موفقیت انجام نشد! ";

            Messages["HVAC_Reera_Diag_tryagain", Language.English] = "Try again later";
            Messages["HVAC_Reera_Diag_tryagain", Language.Farsi] = "در فرصتی دیگر دوباره تلاش نمایید";

            Messages["HVAC_Reera_Diag_EnterRemoteCount", Language.English] = " Enter the number of remotes, from 1 to 4. ";
            Messages["HVAC_Reera_Diag_EnterRemoteCount", Language.Farsi] = " تعداد ریموت را وارد کنید، 1 تا 4 عدد. ";


            Messages["HVAC_Reera_Diag_resetodo", Language.English] = "ODO Value must be lass than 100km\r\nODO Value has not reset before";
            Messages["HVAC_Reera_Diag_resetodo", Language.Farsi] = "میزان پیمایش باید کم تر از 100 کیلومتر باشد\r\nمیزان پیمایش نباید از قبل ریست شده باشد";

            Messages["HVAC_Reera_Diag_RemoteDefinedSuccessfully", Language.English] = " The remote was defined successfully. ";
            Messages["HVAC_Reera_Diag_RemoteDefinedSuccessfully", Language.Farsi] = " ریموت با موفقیت تعریف شد. ";

            Messages["HVAC_Reera_Diag_PressRemoteButton", Language.English] = " Please press one of the first remote buttons.\r\nIn some cases, it is necessary to hold two remote keys simultaneously for 4 seconds. ";
            Messages["HVAC_Reera_Diag_PressRemoteButton", Language.Farsi] = " لطفا یکی از دکمه های ریموت اول را بزنید.\r\nدر بعضی از موارد نیاز است تا دو کلید ریموت به طور همزمان و به مدت 4 ثانیه نگه داشته شوند. ";


        }
    }
}