
/* ***************************************************************** */
/*                                                                   */
/*              Database                                             */
/*                                                                   */
/* ***************************************************************** */


dbase "Banana Bunch"  BananaBunch[20000]{
      
      "Serial Number"   int SN;
      "Bunch Weight"    decimal WR%5.1;
      "Week Old (age)"  int WK;
      "Farm Number"     string FM[4];
      "Parcela Number"  string PC[4];
      "Lot Number"      string BK[7];
      "Gang Number"     string CC[4];
      "Date"            string DATE[10];
      "Time"            string TIME[8];

}


dbase "Banana Sampling"      BananaSampling[1000]{
      "Banana Sampling ID"   int SID;
      "Serial Number"        int SN;
      "Bunch Calibration"    decimal BC%3.1;
      "FingerLength"         decimal FL%3.1;
      "Number of Hands"      decimal NH%3.1;
      "Number of Fingers"    decimal FC%3.1;
      "Harvesting Code"      decimal HC%3.1;       
}
 
 
 dbase "User"     User[5]{
       "User ID"          int UID;
       "Operator ID"      int OperatorID;
       "User Name"        string username[20];   
       "First Name"       string fname[15];
       "Last Name"        string lname[15];
       "Password"         string pass[15]; 
 }

dbase "Last Banana Bunch Setting" LastBananaBunchSetting[2]{
      "Setting ID"             int SID;   
      "Ribbon Value Blue"      int rvblue ;
      "Ribbon ValueBlack"      int rvblack;
      "Ribbon ValueYellow"      int rvyellow;
      "Ribbon ValueGreen"      int rvgreen;
      "Ribbon ValueWhite"      int rvwhite;
      "Ribbon Value Brown"      int rvbrown;
      "Minimum Load"            int rvminLoad;
      "Last Total Weight"      decimal rvLastTotalWeight %5.1;
      "Last Total Bunch"        int rvLastTotalBunch;
      "Last Total Average"      decimal rvLastTotalAve %5.1;
}

dbase "Parcela"                 ParcelaDB[50]{
      "Parcela ID"              int pID;            
      "Total Weight"            decimal parcelaWT %8.1;
      "Total Bunches"           int parcelaBunches;
      "Min Bunch"               decimal minBunch %8.1;
      "Max Bunch"               decimal maxBunch %8.1;
      "Week 7"                  int bWeek7;
      "Week 8"                  int bWeek8;                  
      "Week 9"                  int bWeek9;
      "Week 10"                 int bWeek10;
      "Week 11"                 int bWeek11;
      "Week 12"                 int bWeek12;
}

dbase "Farm"                     FarmDB[50]{
     "Farm ID"                   int fID;          
     "Total Weight"              decimal farmWT %8.1;
     "Total Bunches"             int farmbunches;
}
