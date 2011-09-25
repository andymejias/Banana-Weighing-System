
dbase "Banana Bunch"  BananaBunch[20000]{
      
      "Serial Number"   int SN;
      "Bunch Weight"    decimal WR%5.dp;
      "Week Old (age)"  int WK;
      "Farm Number"     string FM[4];
      "Parcela Number"  int PC;
      "Lot Number"      string BK[7];
      "Gang Number"     string CC[4];
      "Date"            string DATE[10];
      "Time"            string TIME[8];

}


dbase "Banana Sampling"      BananaSampling[1000]{
      "Banana Sampling ID"   int SID;
      "Serial Number"        int SN;
      "Bunch Calibration"    int BC;
      "FingerLength"         int FL;
      "Number of Hands"      int NH;
      "Number of Fingers"    int FC;
      "Harvesting Code"      int HC;       
}
 
 
 dbase "User"     User[5]{
       "User ID"          int UID;
       "Operator ID"      int OperatorID;
       "User Name"        string username[20];   
       "First Name"       string fname[15];
       "Last Name"        string lname[15];
       "Password"         string pass[15]; 
 }

dbase "Last Banana Bunch Setting" LastBananaBunchSetting[5]{
      "Setting ID"             int SID;   
      "Ribbon Value Blue"      int rvblue ;
      "Ribbon ValueBlack"      int rvblack;
      "Ribbon ValueYellow"      int rvyellow;
      "Ribbon ValueGreen"      int rvgreen;
      "Ribbon ValueWhite"      int rvwhite;
      "Ribbon Value Brown"      int rvbrown;
      "Minimum Load"            int rvminLoad;

}

dbase "Parcela"                 ParcelaDB[100]{
      "Parcela ID"              int pID;      
      "Parcela No"              string parcelaNo[3];
      "Total Weight"            decimal parcelaWT %8.1;
}

dbase "Farm"                     FarmDB[1000]{
     "Farm ID"                   int fID;
     "Farm No"                   string farmNo[3];
     "Total Weight"              decimal farmWT %8.1;
}


/* ************************************************************** */
/*                                                                */
/*       V a r i a b l e s                                        */
/*                                                                */
/* ************************************************************** */

          int ribbonColor;
          string farmNo[4];
          int parcelaNo;
          string lotNo[7];
          string gangNo[4];

          int calibrationSample;
          int fingerLenghtSample;
          int numHandsSample;
          int numFingersSample;
          int harverstCodeSample;          

          int rcBlue;
          int rcBlack;
          int rcYellow;
          int rcGreen;
          int rcWhite;
          int rcBrown;
         
          
          decimal oldnet %5.1 ;
          decimal newnet %5.1 ;
          decimal crNet %5.1;
          bool flagUnload;
          int rColor;
          
          
          int sn = 0;
          decimal tw%9.1=0;
          int bsid = 0;
          int minLoad;
          string dpRColor[4];
          
          string csvbuffer[100];
          string formatDate[20];

/* ************************************************************** */
/*                                                                */
/*       Initialization                                           */
/*                                                                */
/* ************************************************************** */


void ribbonColorValue(void){

         LastBananaBunchSetting.SID=1;                   
         if(records(LastBananaBunchSetting)==0){
            LastBananaBunchSetting.rvblue=7;                                    
            LastBananaBunchSetting.rvblack=8;
            LastBananaBunchSetting.rvyellow=9;
            LastBananaBunchSetting.rvgreen=10;
            LastBananaBunchSetting.rvwhite=11;
            LastBananaBunchSetting.rvbrown=12;
            LastBananaBunchSetting.rvminLoad=10;
            
            insert(LastBananaBunchSetting);
         }
        if(find(LastBananaBunchSetting)==0 ){
         
        rcBlue=LastBananaBunchSetting.rvblue;
        rcBlack=LastBananaBunchSetting.rvblack;
        rcYellow=LastBananaBunchSetting.rvyellow;
        rcGreen=LastBananaBunchSetting.rvgreen;
        rcWhite=LastBananaBunchSetting.rvwhite;
        rcBrown=LastBananaBunchSetting.rvbrown;
        minLoad=LastBananaBunchSetting.rvminLoad;
        }
      
 }



















/* ************************************************************** */
/*                                                                */
/*       CSV EXPORTING                                            */
/*                                                                */
/* ************************************************************** */

string dateFormat(string formatDate){
    
     string Day[3] = sub(date,0,2);
     string Month[3] = sub(date,3,2);
     string Year[5] = sub(date,6,4);

     if(Month=="01"){
          Month="January";           
     }else if(Month=="02"){
          Month="February";
     }else if(Month=="03"){
          Month="March";
     }else if(Month=="04"){
          Month="April";      
     }else if(Month=="05"){
           Month="May";
     }else if(Month=="06"){
            Month="June"; 
     }else if(Month=="07"){
           Month="July"; 
     }else if(Month=="08"){
            Month="August";
     }else if(Month=="09"){
           Month="September"; 
     }else if(Month=="10"){
            Month="October"; 
     }else if(Month=="11"){
           Month="November"; 
     }else if(Month=="12"){
            Month="December"; 
     }else {
           break;
     }          
    formatDate=(Month+" "+Day+" 20"+Year);     
    return (formatDate);
}




void formatCSV(string __xlocation){    
       fopen(0,__xlocation+"/Banana_Bunch_Data.csv");       
       csvbuffer= concat("Data from Packing Station 2 Banana Bunch Weighing Unit","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("COMPANY INC","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("Date: "+dateFormat(formatDate)+";" ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}
       csvbuffer= concat("SN,","WR,","WK,","FM,","PC,","BK,","CC," ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}                 
       fclose(0);
}

void formatSamplingCSV(string __xlocation){    
       fopen(0,__xlocation+"/Banana_Bunch_Sampling.csv");       
       csvbuffer= concat("Sampling Data from Packing Station 2 Banana Bunch Weighing Unit","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("COMPANY INC","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("Date: "+dateFormat(formatDate)+";" ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}
       csvbuffer= concat("SID,","SN,","BC,","FL,","NH,","FC,","HC," ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}                 
       fclose(0);
}




void saveBananaBunchCSV(int _sn, decimal _wr, int _wk, string _fm, int _pc, string _bk, string _cc, string _xlocation){
     fopen(0,_xlocation+"/Banana_Bunch_Data.csv");
     csvbuffer= concat(  _sn,"," , _wr,",", _wk,"," , _fm,",", _pc,",",  _bk,",", _cc,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
    fclose(0);
}

void saveBananaSampleCSV(int _SID, int _SN, int _BC, int _FL, int _NH, int _FC, int _HC, string _xlocation){
     fopen(0,_xlocation+"/Banana_Bunch_Sampling.csv");
     csvbuffer= concat(  _SID,"," , _SN,",", _BC,"," , _FL,",", _NH,",",  _FC,",", _HC,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
    fclose(0);
}


/* ************************************************************** */
/*                                                                */
/*      Database Calls                                           */
/*                                                                */
/* ************************************************************** */




void saveBananaBunchWeigh(decimal _crnet){                         
       BananaBunch.SN = sn;
       BananaBunch.WR = _crnet;
       BananaBunch.WK = ribbonColor;
       BananaBunch.FM = farmNo;
       BananaBunch.PC = parcelaNo;
       BananaBunch.BK = lotNo;
       BananaBunch.CC = gangNo;
       BananaBunch.DATE = date;
       BananaBunch.TIME = time;       
       insert(BananaBunch);
}

void saveBananaBunchSampling(void){ 
     BananaSampling.SID=bsid;
     BananaSampling.SN=sn;
     BananaSampling.BC=calibrationSample;
     BananaSampling.FL=fingerLenghtSample;
     BananaSampling.NH=numHandsSample;
     BananaSampling.FC=numFingersSample;
     BananaSampling.HC=harverstCodeSample;     
     insert(BananaSampling);      
 }



/* ************************************************************** */
/*                                                                */
/*      Screen Display                                            */
/*                                                                */
/* ************************************************************** */


void weighBananaBunchScreen(void){
  decimal avetw %8.1;
  avetw = (tw/sn);   
  fctinfo(1,lsub("Data"));    
  font(17);
  fctinfo(2,lsub("Sampling"));    
  font(17);  
  fctinfo(3,lsub("Reports"));    
  font(17);
  fctinfo(4,lsub(""));    
  font(17);
  fctinfo(6,lsub("Exit"));    
  font(17);
  showtext(10,0,lsub("Weighing Banana Bunch"));
  posto(10,20); lineto(310,20);  
  showtext(10,40,"Total No. Bunches : ");  
  showtext(260,40, adj(sn,5,0)+" pcs" ); 
  showtext(10,55,"Total Weight of Bunches : ");  
  showtext(250,55, adj(tw,8,1)+" kgs" );  
  showtext(10,70,"Total Ave. Weight of Bunches : ");  
  showtext(250,70, adj(avetw,8,1)+" kgs" ); 
  showtext(10,85, "Enter Ribbon Color : ");
  showtext(150,85, dpRColor ); 
  showtext(10,100, "Captured weight : ");
  showtext(150,100, adj(crNet,5,1) );   
  font(15);
  fontsize(11);  
}


/* ************************************************************** */
/*                                                                */
/*      Operational Methods                                       */
/*                                                                */
/* ************************************************************** */

void checkPickColor(char ch){

    int inSN;
    if(sn!=0){ 
        inSN=sn-1;
    }else{
        inSN=0;
    }    
     
    if(ch==52){          
          ribbonColor=rcBlue;
          dpRColor="BLU";
    }else if(ch==53){
          ribbonColor=rcBlack;
          dpRColor="BLK";
    }else if(ch==54){
          ribbonColor=rcYellow;
          dpRColor="YLW";
    }else if(ch==55){
          ribbonColor=rcGreen;
          dpRColor="GRN";
    }else if(ch==56){
          ribbonColor=rcWhite;
          dpRColor="WHT";
    }else if(ch==57){
          ribbonColor=rcBrown;
          dpRColor="BRN";
    }       
    BananaBunch.SN=inSN;
    BananaBunch.WK=ribbonColor;
    insert(BananaBunch);
}




void BananaBunchReports(void){



}


void BananaBunchAge(void){
     inputbox("Enter Ribbon Color:"){
         "Ribbon Color"    rColor;            
     }     
     if (rColor==4){
        ribbonColor=rcBlue;        
     }else if (rColor==5){
        ribbonColor=rcBlack;        
     }else if (rColor==6){
        ribbonColor=rcYellow;        
     }else if (rColor==7){
        ribbonColor=rcGreen;        
     }else if (rColor==8){
        ribbonColor=rcWhite;
     }else if (rColor==9){
        ribbonColor=rcBrown;
     }     
     if ( button != ok ) return;
      clearscreen(); 
}


void BananaBunchSampleData(void){

     inputbox("Enter Banana Bunch Sampling Data"){
         "Calibration"            calibrationSample;
         "Finger Lenght"          fingerLenghtSample;
         "Number of Hands"        numHandsSample;
         "Number of Fingers"      numFingersSample;
         "Harvest Code"           harverstCodeSample;          
     }
     saveBananaBunchSampling();
     bsid++;
     if ( button != ok ) return;
      clearscreen(); 
      calibrationSample=0;
      fingerLenghtSample=0;
      numHandsSample=0;
      numFingersSample=0;
      harverstCodeSample=0;
      
}


void BananaBunchData(void){
     
     inputbox("Enter Banana Bunch Data :"){
          
          //"Ribbon Color"    ribbonColor until (ribbonColor>=4 && ribbonColor<=9);
          "Farm Number"     farmNo;
          "Parcela Number"  parcelaNo;
          "Lot Number"      lotNo;
          "Gang Number"     gangNo;                    
     }

    /*
  if (ribbonColor==4){
        ribbonColor=rcBlue;
         dpRColor="BLU";
     }else if (ribbonColor==5){
        ribbonColor=rcBlack;
        dpRColor="BLK";
     }else if (ribbonColor==6){
        ribbonColor=rcYellow;
        dpRColor="YLW";
     }else if (ribbonColor==7){
        ribbonColor=rcGreen;
        dpRColor="GRN";
     }else if (ribbonColor==8){
        ribbonColor=rcWhite;
        dpRColor="WHT";
     }else if (ribbonColor==9){
        ribbonColor=rcBrown;
        dpRColor="BRN";
     }*/

     if ( button != ok ) return;
      clearscreen(); 
}



void WeighingMode(void){

     char ch;
     int  pickColor;
     bool result;    
     
     clearscreen();  
     getweight(indicatedscale());             
     
              
     for(;;){
            
              if (keypressed()){ 
                 ch=readkey(); 
                  delay(0.2);            
                  checkPickColor(ch);
                   if(ch==fct1){
                      BananaBunchData();
                      clearscreen();                  
                   }else if (ch==fct2){
                            BananaBunchSampleData();
                            clearscreen();                      
                   }else if (ch==fct3){
                            BananaBunchReports();
                            clearscreen();                            
                   }else if(ch==fct4){
                            clearscreen();
                   }else if(ch==fct6){
                         break;                  
                   }                          
             }else{
                ch=0;                
             }
            
           
            
            weighBananaBunchScreen();    
                   
             
            if((getweight()==0) && (net>minLoad) && issettled){                                                       
                if (flagUnload){
                         crNet=net;             
                         tw=tw+crNet;                                                                                                                            
                         saveBananaBunchWeigh(crNet);                          
                         clearscreen(); 
                         sn++  ;                       
                }                
                oldnet = net;                                 
                flagUnload = false;               
             }

             
             if(net<=minLoad){                 
                 flagUnload=true;                  
             }
            
            delay(0.1);
     }     
}




/* ************************************************************** */
/*                                                                */
/*      Supervisor Mode                                           */
/*                                                                */
/* ************************************************************** */

void checkStartofDay(void){
     
     bool f;

     if( records(BananaBunch)!=0 || records(BananaSampling)!=0){
         yesnobox(" Old Entry in Database detected! \n Do you want to clear database \n and csv file??", f);
         if(f){
               clear(BananaBunch);
               clear(BananaSampling);
               fremove("shared/Banana_Bunch_Data.csv");
               fremove("shared/Banana_Bunch_Sampling.csv");
               farmNo="";
               parcelaNo=0;
               lotNo="";
               gangNo="";    
               tw=0;
               sn=0;
               calibrationSample=0;
               fingerLenghtSample=0;
               numHandsSample=0;
               numFingersSample=0;
               harverstCodeSample=0;               
               infobox("cleaning up database and csv");
               delay(0.5);
               break;
         }else{
               break;
         }         
     }
}



void  exportSpreadsheetINTERNAL(void){
      int i;
      int j;
      int xList;
      int yList;

      int _sn;
      decimal _wr%5.1;
      int _wk;
      string _fm[4];
      int _pc;
      string _bk[7];
      string _cc[4];

      
      int _SID;
      int _SN;
      int _BC;
      int _FL;
      int _NH;
      int _FC;
      int _HC;
      string _location[10];

      _location="shared";

      if(fexists(_location+"/Banana_Bunch_Data.csv")){
         fremove(_location+"/Banana_Bunch_Data.csv");
         formatCSV(_location);         
      }else{
         formatCSV(_location);
      }


      if(fexists(_location+"/Banana_Bunch_Sampling.csv")){
         fremove(_location+"/Banana_Bunch_Sampling.csv");
         formatSamplingCSV(_location);                                                          
      }else{
         formatSamplingCSV(_location);
      }

         
      xList = records(BananaBunch);
      
      for(i=0; i<xList;i++){
               
               BananaBunch.SN=i;
               if(find(BananaBunch)==0){
                    _sn=BananaBunch.SN;
                    _wr=BananaBunch.WR;
                    _wk=BananaBunch.WK;
                    _fm=BananaBunch.FM;
                    _pc=BananaBunch.PC;
                    _bk=BananaBunch.BK;
                    _cc=BananaBunch.CC;                   
               
               }
         
         saveBananaBunchCSV(_sn, _wr, _wk, _fm, _pc, _bk, _cc, _location);         
                     
      }

  
      
      yList = records(BananaSampling);
      
      for(j=0; j<yList;j++){
               BananaSampling.SID = j;
               if(find(BananaSampling)==0){
                     _SID = BananaSampling.SID;
                     _SN = BananaSampling.SN;
                     _BC = BananaSampling.BC;
                     _FL = BananaSampling.FL;
                     _NH = BananaSampling.NH;                   
                     _FC = BananaSampling.FC;
                     _HC = BananaSampling.HC;               
               }
               
               saveBananaSampleCSV(_SID, _SN, _BC, _FL, _NH, _FC, _HC, _location); 
      }


      infobox("exported to CSV");
      delay(0.5);

}

void  exportSpreadSheetUSB(void){
      int i;
      int j;
      int xList;
      int yList;

      int _sn;
      decimal _wr%5.1;
      int _wk;
      string _fm[4];
      int _pc;
      string _bk[7];
      string _cc[4];

      
      int _SID;
      int _SN;
      int _BC;
      int _FL;
      int _NH;
      int _FC;
      int _HC;
      string _location[10];

      _location= "usbstick";


      if(fexists(_location+"/Banana_Bunch_Data.csv")){
         fremove(_location+"/Banana_Bunch_Data.csv");
         formatCSV(_location);         
      }else{
         formatCSV(_location);
      }


      if(fexists(_location+"/Banana_Bunch_Sampling.csv")){
         fremove(_location+"/Banana_Bunch_Sampling.csv");
         formatSamplingCSV(_location);                                                          
      }else{
         formatSamplingCSV(_location);
      }


      
      xList = records(BananaBunch);
      
      for(i=0; i<xList;i++){
               
               BananaBunch.SN=i;
               if(find(BananaBunch)==0){
                    _sn=BananaBunch.SN;
                    _wr=BananaBunch.WR;
                    _wk=BananaBunch.WK;
                    _fm=BananaBunch.FM;
                    _pc=BananaBunch.PC;
                    _bk=BananaBunch.BK;
                    _cc=BananaBunch.CC;                   
               
               }
         
         saveBananaBunchCSV(_sn, _wr, _wk, _fm, _pc, _bk, _cc, _location);         
                     
      }

  
      
      yList = records(BananaSampling);
      
      for(j=0; j<yList;j++){
               BananaSampling.SID = j;
               if(find(BananaSampling)==0){
                     _SID = BananaSampling.SID;
                     _SN = BananaSampling.SN;
                     _BC = BananaSampling.BC;
                     _FL = BananaSampling.FL;
                     _NH = BananaSampling.NH;                   
                     _FC = BananaSampling.FC;
                     _HC = BananaSampling.HC;               
               }
               
               saveBananaSampleCSV(_SID, _SN, _BC, _FL, _NH, _FC, _HC, _location); 
      }


      infobox("exported to CSV");
      delay(0.5);

}

void selectexportSpreadSheet(void){     

 
     selectbox("Select location to save :"){
               "USB STICK"         exportSpreadSheetUSB();
               "Internal Memory"   exportSpreadsheetINTERNAL();            
     }
     
}


void setRibbonColorValue(void){
     inputbox("Ribbon Color Value :"){
            "Blue"         rcBlue;
            "Black"        rcBlack;
            "Yellow"       rcYellow;
            "Green"        rcGreen;
            "White"        rcWhite;
            "Brown"        rcBrown;                     
     }
     clear(LastBananaBunchSetting); 
     LastBananaBunchSetting.SID=1;    
     LastBananaBunchSetting.rvblue=rcBlue;
     LastBananaBunchSetting.rvblack=rcBlack;
     LastBananaBunchSetting.rvyellow=rcYellow;
     LastBananaBunchSetting.rvgreen=rcGreen;
     LastBananaBunchSetting.rvwhite=rcWhite;
     LastBananaBunchSetting.rvbrown=rcBrown;
     insert(LastBananaBunchSetting);

     infobox("saving ribbon color value...");
     delay(0.5);
}

void setMinLoad(void){
     
     char ch;

      

     inputbox("Set Minimum Weigh Value :"){
     
          "Minimum Load :"  minLoad;
     
     }
     if(keypressed()){
           ch=readkey();                   
     }
     
     if(ch==fct6){    
                  break;
    }else{
     
     LastBananaBunchSetting.SID=1;
     LastBananaBunchSetting.rvminLoad=minLoad;
     insert(LastBananaBunchSetting);
     
     infobox("saving minimum weigh value...");
     delay(0.5);
     }
     
}


void eraseAllData(void){
     clear(BananaBunch);
     clear(BananaSampling);
     fremove("shared/Banana_Bunch_Data.csv");
     fremove("shared/Banana_Bunch_Sampling.csv");
     
    farmNo="";
    parcelaNo=0;
    lotNo="";
    gangNo="";
    
    tw=0;
    sn=0;

     calibrationSample=0;
     fingerLenghtSample=0;
     numHandsSample=0;
     numFingersSample=0;
     harverstCodeSample=0;         
     
     minLoad=0;
          
     infobox("all data are erased...");
     delay(0.5);
}

void bananaWeighingSetting(void){

    selectbox("Select Banana Weighing Setting"){
          "Set Ribbon Color Value" setRibbonColorValue();
          "Set Minimum Weigh" setMinLoad();
          "Export Data to SpreadSheet"     selectexportSpreadSheet();
          
    }

}

void setDateTime(void){
     inputbox("Set Time and Date : "){     
       "Time "      time;
       "Date "      date;
     }     
}

void  supervisorMode(void){
      string  UserPassword[4]="1234";
      codebox("Please enter password ", UserPassword );
      if(button == ok)
            selectbox("Settings"){
                "Banana Bunch Data edit"             edit(BananaBunch);
                "Time and Date Settings"             setDateTime();
                "Erase All Data"                     eraseAllData();
            }      
}



/* ************************************************************** */
/*                                                                */
/*       Main Program                                             */
/*                                                                */
/* ************************************************************** */


void main(void)
{
  
  checkStartofDay();  
  ribbonColorValue();  
  
  for(;;){
     selectbox("Main Menu                        IT-6000E - COMPANY"){
       "Banana Weighing"    WeighingMode();
       "Banana Weighing Settings" bananaWeighingSetting();
       "Supervisor Mode" supervisorMode();
       
     } 
   }  
}
