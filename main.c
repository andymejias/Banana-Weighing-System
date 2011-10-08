
/* ****************************************************************** */
/* ****************************************************************** */
/* *                                                                * */
/* *                                                                * */
/* *                                                                * */
/* *                        RTC-Program                             * */
/* *                                                                * */
/* *                 Copyright by Clinicom                          * */
/* *                                                                * */
/* ****************************************************************** */
/* ****************************************************************** */

/*

 Costumer:                TADECO                                              

 Project:                IT6000-E TADECO Banana Weighing System

 Creation date:          Sept 2011

 Author:                 Edu Mejias, Ferd Tomale


*/




#include "TadecoDBase.c"
#include "http_client.h"


/* ************************************************************** */
/*                                                                */
/*       V a r i a b l e s                                        */
/*                                                                */
/* ************************************************************** */

          int ribbonColor;
          int farmNo;
          string _farmNo[3];
          int parcelaNo;
          string _parcelaNo[3];
          string lotNo[7];
          string gangNo[4];

          decimal calibrationSample%3.1;
          decimal fingerLenghtSample%3.1;
          decimal numHandsSample%3.1;
          decimal numFingersSample%3.1;
          decimal harverstCodeSample%3.1;          

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
          
          
          int sn ;
          int farm30count;
          int farm31count;
          int farm32count;
          int parcela88count;
          int parcela89count;
          int parcela90count;
          int parcela91count;
          int parcela92count;
          int parcela93count;
          int parcela94count;
          int parcela95count;
          int parcela96count;
          decimal tw%9.1;
          decimal avetw %9.1;
          int bsid = 1;
          int minLoad;
          string dpRColor[4];
          
          string csvbuffer[100];
          string formatDate[20];
          
          string rFarmNo[2];
          string r2FarmNo[2];
          string r3FarmNo[2];          
         
          
/* ************************************************************** */
/*                                                                */
/*       Initialization                                           */
/*                                                                */
/* ************************************************************** */

#include "http_client.c"

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

void FarmData(void){
     int x;

     for(x=30; x<33; x++){     
             FarmDB.fID = x;
             FarmDB.farmWT = 0;
             insert(FarmDB);     
     }
}

void ParcelaData(void){
     int x;
     
     for(x=88;x<97;x++){
         ParcelaDB.pID = x;
         ParcelaDB.parcelaWT = 0;
         insert(ParcelaDB);
     }    
          
}






void checkStartofDay(void){
     
     bool f;
     f=false;

     if( records(BananaBunch)!=0 || records(BananaSampling)!=0){
         yesnobox(" Old Entry in Database detected! \n Do you want to clear database \n and csv file??", f);
         if(f==true){
               clear(BananaBunch);
               clear(BananaSampling);
               clear(ParcelaDB);
               clear(FarmDB);               
               FarmData();
               ParcelaData(); 
               
               fremove("shared/TADECO_Banana_Bunch_Data.csv");
               fremove("shared/TADECO_Banana_Bunch_Sampling.csv");
               farmNo="";
               parcelaNo="";
               lotNo="";
               gangNo="";
               rFarmNo="";
               r2FarmNo="";               
               tw=0;
               sn=0;
               avetw = 0;
               bsid = 1;
               farm30count=0;
               farm31count=0;
               farm32count=0;
               parcela88count=0;
               parcela89count=0;
               parcela90count=0;
               parcela91count=0;
               parcela92count=0;
               parcela93count=0;
               parcela94count=0;
               parcela95count=0;
               parcela96count=0;
               calibrationSample=0;
               fingerLenghtSample=0;
               numHandsSample=0;
               numFingersSample=0;
               harverstCodeSample=0;
               LastBananaBunchSetting.SID=1;
              
               if(findfield(LastBananaBunchSetting, SID)==0){
                             LastBananaBunchSetting.rvLastTotalBunch=0;
                             LastBananaBunchSetting.rvLastTotalWeight=0;
                             LastBananaBunchSetting.rvLastTotalAve=0;
                             insert(LastBananaBunchSetting);               
               }  
             
               infobox("cleaning up database and csv");              
               delay(0.5);
               break;
         }else {
               
               //sn = records(BananaBunch);
               
             
               LastBananaBunchSetting.SID=1;
               if(findfield(LastBananaBunchSetting, SID)==0){
               sn = LastBananaBunchSetting.rvLastTotalBunch;
               tw = LastBananaBunchSetting.rvLastTotalWeight;               
               }
               
               avetw = tw/sn;
               
               break;
         }         
     }
}









/* ************************************************************** */
/*                                                                */
/*       CSV EXPORTING                                            */
/*                                                                */
/* ************************************************************** */

#include "dateFormatCSV.c"


//CSV header location
#include "CSVHeaders.c"



// CSV Saving location

#include "CSVSaving.c"



/* ************************************************************** */
/*                                                                */
/*      Database Calls                                           */
/*                                                                */
/* ************************************************************** */




void saveBananaBunchWeigh(decimal _crnet, decimal _tw){                         
       decimal totalFarmWeight%8.1;
       decimal totalParcelaWeight%8.1; 
       decimal minbunchnet %8.1;
       decimal maxbunchnet %8.1;
       decimal _totalavebunch %5.1;
       int __sn;
       int countAge7;
       int countAge8;
       int countAge9;
       int countAge10;
       int countAge11;
       int countAge12;
       
       countAge7=0;
       countAge8=0;
       countAge9=0;
       countAge10=0;
       countAge11=0;
       countAge12=0;
       
       
       
       LastBananaBunchSetting.SID=1;
       if(findfield(LastBananaBunchSetting, SID)==0){
            __sn=sn+1;
            LastBananaBunchSetting.rvLastTotalWeight = tw;
            LastBananaBunchSetting.rvLastTotalBunch = __sn;
            _totalavebunch = tw/sn;
            LastBananaBunchSetting.rvLastTotalAve = _totalavebunch;  
            insert(LastBananaBunchSetting);                                          
       }
       
       
              
       BananaBunch.SN = sn;
       BananaBunch.WR = _crnet;
       BananaBunch.WK = ribbonColor;       
       BananaBunch.FM = adj(farmNo,3,0);  
       BananaBunch.PC = adj(parcelaNo,3,0);
       BananaBunch.BK = lotNo;
       BananaBunch.CC = gangNo;
       gettime();
       BananaBunch.DATE = date;
       BananaBunch.TIME = time;       
        if((insert(BananaBunch))==2){
              infobox("memory full");
              delay(5.0);
              
              break;                       
        } else {
          // do http post
          // in post data:
          // { = %7B
          // " = %22
          // : = %3A
          // , = %2C
          // } = %7D
          // log={"param1":"value1","param2":"value2"}
          // becomes
          // log=%7B%22param1%22%3A%22value1%22%2C%22param2%22%3A%22value2%22%7D 
          
          http_client_post(
            8,
            "192.168.2.100", 
            "80", 
            "index.php", 
            "tadecows.local", 
            //"log=%7B%22fm%22%3A%22999%22%2C%22bk%22%3A%22999%22;%2C%22pc%22%3A%2299%22%2C%22wk%22%2C%2299%22%2C%22wr%22%2C%2299999%22%2C%22cc%22%2C%22999%22%2C%22dt%22%3A%2210%2F07%2F2011+10%3A10%22%7D"
            "log=%7B%22fm%22%3A%22"+adj(farmNo,3,0)+"%22%2C%22bk%22%3A%22"+lotNo+"%22%2C%22pc%22%3A%22"+adj(parcelaNo,3,0)+"%22%2C%22wk%22%2C%22"+adj(ribbonColor,3,0)+"%22%2C%22wr%22%2C%22"+adj(_crnet,5,1)+"%22%2C%22cc%22%2C%22"+gangNo+"%22%2C%22dt%22%3A%2210%2F07%2F2011+10%3A10%22%7D"
          );
        }
       

       
       
       switch(farmNo){
       
          case 30:
                FarmDB.fID=30;
                if(findfield(FarmDB, fID)==0){
                farm30count++;
                totalFarmWeight = FarmDB.farmWT;                
                totalFarmWeight = _crnet+totalFarmWeight;            
                FarmDB.farmWT=totalFarmWeight;
                FarmDB.farmbunches=farm30count;
                insert(FarmDB);
                switch(parcelaNo){
                      case 88:
                            ParcelaDB.pID=88;
                            if(findfield(ParcelaDB,pID)==0){
                            parcela88count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela88count;                            
                            
                            minbunchnet = ParcelaDB.minBunch;                            
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            //counting by Age                                                
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7=countAge7 + 1;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}
                            
                            
                            insert(ParcelaDB);
                            }
                            break;
                      case 89:
                            ParcelaDB.pID=89;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela89count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela89count;
                            
                            minbunchnet = ParcelaDB.minBunch;
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            
                             //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}

                            
                            insert(ParcelaDB);
                            }
                            break;
                      case 90:
                            ParcelaDB.pID=90;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela90count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela90count;
                            
                            minbunchnet = ParcelaDB.minBunch;                            
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}

                            
                            insert(ParcelaDB);
                            }
                            break;                      
                      default:
                            break;                
                }              
                
                }
                break;
          case 31:
                FarmDB.fID=31;
                if(findfield(FarmDB, fID)==0){
                farm31count++;
                totalFarmWeight = FarmDB.farmWT;                
                totalFarmWeight = _crnet+totalFarmWeight;            
                FarmDB.farmWT=totalFarmWeight;
                FarmDB.farmbunches=farm31count;
                insert(FarmDB);
                 switch(parcelaNo){
                      case 91:
                            ParcelaDB.pID=91;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela91count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela91count;
                            
                            minbunchnet = ParcelaDB.minBunch;                            
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                             //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}

                            
                            insert(ParcelaDB);
                            } 
                            break;
                      case 92:
                            ParcelaDB.pID=92;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela92count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela92count;

                            minbunchnet = ParcelaDB.minBunch;                            
                             if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                             //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}

                            
                            insert(ParcelaDB);
                            }
                            break;
                      case 93:
                            ParcelaDB.pID=93;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela93count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela93count;

                            minbunchnet = ParcelaDB.minBunch;                            
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                             //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}
                            
                            insert(ParcelaDB);
                            }
                            break;                      
                      default:
                            break;                
                }
                }
                break;
          case 32:
                FarmDB.fID=32;
                if(findfield(FarmDB, fID)==0){
                farm32count++;
                totalFarmWeight = FarmDB.farmWT;                
                totalFarmWeight = _crnet+totalFarmWeight;            
                FarmDB.farmWT=totalFarmWeight;
                FarmDB.farmbunches=farm32count;
                insert(FarmDB);
                 switch(parcelaNo){
                      case 94:
                            ParcelaDB.pID=94;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela94count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela94count;
                            
                            minbunchnet = ParcelaDB.minBunch;                                      
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}
                                                       
                            
                            insert(ParcelaDB);
                            }
                            break;
                      case 95:
                            ParcelaDB.pID=95;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela95count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela95count;

                            minbunchnet = ParcelaDB.minBunch;                            
                             if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}
                  
                            
                            insert(ParcelaDB);
                            }
                            break;
                      case 96:
                            ParcelaDB.pID=96;
                            if(findfield(ParcelaDB, pID)==0){
                            parcela96count++;
                            totalParcelaWeight = ParcelaDB.parcelaWT;                
                            totalParcelaWeight = _crnet+totalParcelaWeight;            
                            ParcelaDB.parcelaWT=totalParcelaWeight;
                            ParcelaDB.parcelaBunches=parcela96count;
                            
                            minbunchnet = ParcelaDB.minBunch;                            
                            if(minbunchnet==0){ minbunchnet=_crnet;              
                            }else{ minbunchnet = ParcelaDB.minBunch; }                         
                            
                            if(minbunchnet > _crnet){ minbunchnet = _crnet ;}
                            ParcelaDB.minBunch = minbunchnet;
                            maxbunchnet = ParcelaDB.maxBunch;
                                if(maxbunchnet < _crnet){ maxbunchnet = _crnet ;}        
                            ParcelaDB.maxBunch = maxbunchnet;
                            
                            //counting by Age                    
                            
                            if(ribbonColor==7){
                                    countAge7 = ParcelaDB.bWeek7;
                                    countAge7++;
                                    ParcelaDB.bWeek7=countAge7; 
                            }else if(ribbonColor==8){
                                    countAge8 = ParcelaDB.bWeek8;
                                    countAge8++;
                                    ParcelaDB.bWeek8=countAge8;
                            }else if(ribbonColor==9){
                                    countAge9 = ParcelaDB.bWeek9;
                                    countAge9++;
                                    ParcelaDB.bWeek9=countAge9;                            
                            }else if(ribbonColor==10){
                                   countAge10 = ParcelaDB.bWeek10;
                                   countAge10++;
                                   ParcelaDB.bWeek10=countAge10;
                            }else if(ribbonColor==11){
                                   countAge11 = ParcelaDB.bWeek11;
                                   countAge11++;
                                   ParcelaDB.bWeek11=countAge11;
                            }else if(ribbonColor==12){
                                   countAge12 = ParcelaDB.bWeek12;
                                   countAge12++;
                                   ParcelaDB.bWeek12=countAge12;
                            }else { infobox("error saving statistics..");}

                            
                            insert(ParcelaDB);
                            }
                            break;                      
                      default:
                            break;                
                }
                
                }
                break;
          default:
                  break;       
       }
       
      
       
       
       
       
 
       
       sn++;
       
       
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
#include "weighingScreens.c"



/* ************************************************************** */
/*                                                                */
/*      Inputbox Conditions                                       */
/*                                                                */
/* ************************************************************** */

void farmConditions(int cfarmNo){
     

     if(cfarmNo==30){
            parcelaNo = 88 || 89 || 90; 
     
     }else if(cfarmNo==31){
           parcelaNo = 91 || 92 || 93;
     }else if(cfarmNo==32){
           parcelaNo = 94 || 95 || 96;
     
     }else {
           infobox("no farm number specified..");
           delay(1.0);
     }
     
    // return parcelaNo;     

}


/* ************************************************************** */
/*                                                                */
/*      Reports                                                   */
/*                                                                */
/* ************************************************************** */

void rptAverageDisplay(string farmNumber, decimal farmAveweigh, decimal farmTotBunch, string fPrcNo, string sPrcNo, string tPrcNo, decimal fPrctBunch, decimal sPrctBunch, decimal tPrctBunch, decimal fPrcABunch, decimal sPrcABunch, decimal tPrcABunch){
     clearscreen();
     reportFarmScreen();

     begindraw();
     //Farm display
     showtext(50,5,farmNumber);
     showtext(165,5,adj(farmTotBunch,5,0));
     showtext(250,5,adj(farmAveweigh,5,1)+" "+unit);
     
     //Parcela display 
     showtext(45,50,fPrcNo);
     showtext(120,50,adj(fPrctBunch,5,0)+" bunches");
     showtext(250,50,adj(fPrcABunch,5,1)+" "+unit);
     
     showtext(45,75,sPrcNo);
     showtext(120,75,adj(sPrctBunch,5,0)+" bunches");
     showtext(250,75,adj(sPrcABunch,5,1)+" "+unit);
     
     showtext(45,100,tPrcNo);
     showtext(120,100,adj(tPrctBunch,5,0)+" bunches");
     showtext(250,100,adj(tPrcABunch,5,1)+" "+unit);

     enddraw();

}



void rptMinMaxDisplay(string _r2FarmNo, string _r2parecelaID1, string _r2parecelaID2, string _r2parecelaID3, decimal _rp1minbunchnet, decimal _rp2minbunchnet , decimal _rp3minbunchnet, decimal _rp1maxbunchnet, decimal _rp2maxbunchnet, decimal _rp3maxbunchnet){
      clearscreen();
      reportParcelaMinMaxScreen();

      begindraw();
     //Farm display
     showtext(50,5,_r2FarmNo);
     
     
     //Parcela display 
     showtext(45,50, _r2parecelaID1);
     showtext(120,50,adj(_rp1minbunchnet,5,1)+" "+unit);
     showtext(250,50,adj(_rp1maxbunchnet,5,1)+" "+unit);
     
     showtext(45,75,_r2parecelaID2);
     showtext(120,75,adj(_rp2minbunchnet,5,1)+" "+unit);
     showtext(250,75,adj(_rp2maxbunchnet,5,1)+" "+unit);
     
     showtext(45,100,_r2parecelaID3);
     showtext(120,100,adj(_rp3minbunchnet,5,1)+" "+unit);
     showtext(250,100,adj(_rp3maxbunchnet,5,1)+" "+unit);

     enddraw();

}

void rptBunchesperAgeDisplay(string _r3FarmNo, string _r3parecelaID1, string _r3parecelaID2, string _r3parecelaID3, int _wk7, int _wk8 , int _wk9, int _wk10, int _wk11, int _wk12){
     clearscreen();   
      reportBunchesperAgeScreen();

     begindraw();
     
      
     
     
     enddraw();
}


void reportsAveFarm(void){
     char ch;
    
     decimal rtotalFarmWeigh %8.1;   
     decimal raveFarmWeigh %8.1;
     decimal r1totalFarmBunch %5.dp;      
     decimal rp1totalParcelaWeigh %8.1; 
     decimal rp2totalParcelaWeigh %8.1;
     decimal rp3totalParcelaWeigh %8.1;
     decimal rp1aveParcelaWeigh %8.1;
     decimal rp2aveParcelaWeigh %8.1;
     decimal rp3aveParcelaWeigh %8.1;      
     
     decimal rp1totalParcelaBunch %5.dp;
     decimal rp2totalParcelaBunch %5.dp;
     decimal rp3totalParcelaBunch %5.dp;
     string rparecelaID1[2];
     string rparecelaID2[2];
     string rparecelaID3[2];
     
     if(rFarmNo==""){ rFarmNo="30";}
     
     
     if(rFarmNo=="30"){
           FarmDB.fID=30;
           if(findfield(FarmDB, fID)==0){
              rtotalFarmWeigh = FarmDB.farmWT;
             r1totalFarmBunch = FarmDB.farmbunches;                  
           }

           ParcelaDB.pID=88;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp1totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=89;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID2 = adj(ParcelaDB.pID,2,0);
              rp2totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp2totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=90;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID3 = adj(ParcelaDB.pID,2,0);
              rp3totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp3totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }          
     
     }else if(rFarmNo=="31"){
           FarmDB.fID=31;
           if(findfield(FarmDB, fID)==0){
              rtotalFarmWeigh = FarmDB.farmWT;
              r1totalFarmBunch = FarmDB.farmbunches;                  
           }

           ParcelaDB.pID=91;           
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp1totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=92;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID2 = adj(ParcelaDB.pID,2,0);
              rp2totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp2totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=93;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID3 = adj(ParcelaDB.pID,2,0);
              rp3totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp3totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }          
     
     }else if (rFarmNo=="32"){
           FarmDB.fID=32;
           if(findfield(FarmDB, fID)==0){
              rtotalFarmWeigh = FarmDB.farmWT;
              r1totalFarmBunch = FarmDB.farmbunches;                  
           }

           ParcelaDB.pID=94;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp1totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=95;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID2 = adj(ParcelaDB.pID,2,0);
              rp2totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp2totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           }
           
           ParcelaDB.pID=96;
           if(findfield(ParcelaDB, pID)==0){
              rparecelaID3 = adj(ParcelaDB.pID,2,0);
              rp3totalParcelaWeigh = ParcelaDB.parcelaWT;
              rp3totalParcelaBunch = ParcelaDB.parcelaBunches;                  
           } 
           
                 
                    
     
     }else {
           infobox("no farm number received....");
           delay (2.0);
     }
     
     raveFarmWeigh = (rtotalFarmWeigh/r1totalFarmBunch);
     rp1aveParcelaWeigh =(rp1totalParcelaWeigh/rp1totalParcelaBunch);
     rp2aveParcelaWeigh =(rp2totalParcelaWeigh/rp2totalParcelaBunch);
     rp3aveParcelaWeigh =(rp3totalParcelaWeigh/rp3totalParcelaBunch);
      
     rptAverageDisplay(rFarmNo, raveFarmWeigh, r1totalFarmBunch, rparecelaID1, rparecelaID2, rparecelaID3, rp1totalParcelaBunch, rp2totalParcelaBunch , rp3totalParcelaBunch, rp1aveParcelaWeigh, rp2aveParcelaWeigh, rp3aveParcelaWeigh);

      
                 

     for(;;){
              if(keypressed()){
                 ch=readkey();
                 if(ch==fct6){
                     break;         
                 }else if(ch==fct1){
                     rFarmNo="30";
                     reportsAveFarm();
                     break;         
                 }else if(ch==fct2){
                     rFarmNo="31";
                     reportsAveFarm();
                     break;         
                 }else if(ch==fct3){
                     rFarmNo="32";
                     reportsAveFarm();
                     break;         
                 }               
                 
             }
     }

}

void reportsMinMaxBunches(void){
     char ch;
     decimal rp1minbunchnet %8.1;
     decimal rp2minbunchnet %8.1;
     decimal rp3minbunchnet %8.1;
     decimal rp1maxbunchnet %8.1;     
     decimal rp2maxbunchnet %8.1;     
     decimal rp3maxbunchnet %8.1;
     string r2parecelaID1[2];
     string r2parecelaID2[2];
     string r2parecelaID3[2];
     
     
     if(r2FarmNo==""){ r2FarmNo="30";}
     
     
     if(r2FarmNo=="30"){
          
           ParcelaDB.pID=88;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1minbunchnet = ParcelaDB.minBunch;
              rp1maxbunchnet = ParcelaDB.maxBunch;              
           }
           
           ParcelaDB.pID=89;
           if(findfield(ParcelaDB, pID)==0){
             r2parecelaID2 = adj(ParcelaDB.pID,2,0);
             rp2minbunchnet = ParcelaDB.minBunch;
             rp2maxbunchnet = ParcelaDB.maxBunch;                 
           }
           
           ParcelaDB.pID=90;
           if(findfield(ParcelaDB, pID)==0){
             r2parecelaID3 = adj(ParcelaDB.pID,2,0);
             rp3minbunchnet = ParcelaDB.minBunch;
             rp3maxbunchnet = ParcelaDB.maxBunch;                  
           }          
     
     }else if(r2FarmNo=="31"){
           
           ParcelaDB.pID=91;           
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1minbunchnet = ParcelaDB.minBunch;
              rp1maxbunchnet = ParcelaDB.maxBunch;                        
           }
           
           ParcelaDB.pID=92;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID2 = adj(ParcelaDB.pID,2,0);
              rp2minbunchnet = ParcelaDB.minBunch;
              rp2maxbunchnet = ParcelaDB.maxBunch;                        
           }
           
           ParcelaDB.pID=93;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID3 = adj(ParcelaDB.pID,2,0);
              rp3minbunchnet = ParcelaDB.minBunch;
              rp3maxbunchnet = ParcelaDB.maxBunch;                        
           }          
     
     }else if (r2FarmNo=="32"){
          
           ParcelaDB.pID=94;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID1 = adj(ParcelaDB.pID,2,0);
              rp1minbunchnet = ParcelaDB.minBunch;
              rp1maxbunchnet = ParcelaDB.maxBunch;                   
           }
           
           ParcelaDB.pID=95;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID2 = adj(ParcelaDB.pID,2,0);
              rp2minbunchnet = ParcelaDB.minBunch;
              rp2maxbunchnet = ParcelaDB.maxBunch;                  
           }
           
           ParcelaDB.pID=96;
           if(findfield(ParcelaDB, pID)==0){
              r2parecelaID3 = adj(ParcelaDB.pID,2,0);
              rp3minbunchnet = ParcelaDB.minBunch;
              rp3maxbunchnet = ParcelaDB.maxBunch;                 
           } 
           
                 
                    
     
     }else {
           infobox("no farm number received....");
           delay (2.0);
     }    
     
     
     rptMinMaxDisplay(r2FarmNo, r2parecelaID1, r2parecelaID2, r2parecelaID3, rp1minbunchnet, rp2minbunchnet , rp3minbunchnet, rp1maxbunchnet, rp2maxbunchnet, rp3maxbunchnet);
     
    
     
     
     
      for(;;){
              if(keypressed()){
                 ch=readkey();
                 if(ch==fct6){
                     break;         
                 }else if(ch==fct1){
                     r2FarmNo="30";
                     reportsMinMaxBunches();
                     break;         
                 }else if(ch==fct2){
                     r2FarmNo="31";
                     reportsMinMaxBunches();
                     break;         
                 }else if(ch==fct3){
                     r2FarmNo="32";
                    reportsMinMaxBunches();
                     break;         
                 }    

              }
      }         
}


void reportsBunchesperAge(void){
     int numBunchRecords;     
     char ch;
     
     int wk7;
     int wk8;
     int wk9;
     int wk10;
     int wk11;
     int wk12;
     string r3parecelaID1[2];
     string r3parecelaID2[2];
     string r3parecelaID3[2];
     
     
     clearscreen();    


     if(r3FarmNo==""){ r3FarmNo="30";}
     
     
     if(r3FarmNo=="30"){
          
           ParcelaDB.pID=88;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID1 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
              
           }
           
           ParcelaDB.pID=89;
           if(findfield(ParcelaDB, pID)==0){
             r3parecelaID2 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }
           
           ParcelaDB.pID=90;
           if(findfield(ParcelaDB, pID)==0){
             r3parecelaID3 = adj(ParcelaDB.pID,2,0);
             wk7 = ParcelaDB.bWeek7;
             wk8 = ParcelaDB.bWeek8;
             wk9 = ParcelaDB.bWeek9;
             wk10 = ParcelaDB.bWeek10;
             wk11 = ParcelaDB.bWeek11;
             wk12 = ParcelaDB.bWeek12;            
           }          
     
     }else if(r3FarmNo=="31"){
           
           ParcelaDB.pID=91;           
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID1 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }
           
           ParcelaDB.pID=92;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID2 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }
           
           ParcelaDB.pID=93;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID3 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }          
     
     }else if (r3FarmNo=="32"){
          
           ParcelaDB.pID=94;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID1 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }
           
           ParcelaDB.pID=95;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID2 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           }
           
           ParcelaDB.pID=96;
           if(findfield(ParcelaDB, pID)==0){
              r3parecelaID3 = adj(ParcelaDB.pID,2,0);
              wk7 = ParcelaDB.bWeek7;
              wk8 = ParcelaDB.bWeek8;
              wk9 = ParcelaDB.bWeek9;
              wk10 = ParcelaDB.bWeek10;
              wk11 = ParcelaDB.bWeek11;
              wk12 = ParcelaDB.bWeek12;
           } 
           
                 
                    
     
     }else {
           infobox("no farm number received....");
           delay (2.0);
     }    
     


    // rptBunchesperAgeDisplay(r3FarmNo, r3parecelaID1, r3parecelaID2, r3parecelaID3, wk7, wk8 , wk9, wk10, wk11, wk12);
     
     
     

   

       for(;;){
              if(keypressed()){
                 ch=readkey();
                 if(ch==fct6){
                     break;         
                 }else if(ch==fct1){
                     r3FarmNo="30";
                     reportsBunchesperAge();
                     break;         
                 }else if(ch==fct2){
                     r3FarmNo="31";
                     reportsBunchesperAge();
                     break;         
                 }else if(ch==fct3){
                     r3FarmNo="32";
                    reportsBunchesperAge();
                     break;         
                 }      

              }
      }     

}

/* ************************************************************** */
/*                                                                */
/*      Operational Methods                                       */
/*                                                                */
/* ************************************************************** */

void checkPickColor(char ch){
    string pkclrParcela[4];
    int pkclrPID;
    int countAge7;
    int countAge8;
    int countAge9;
    int countAge10;
    int countAge11;
    int countAge12;
    int _tempWK;
    string _tempParcela[2];
    
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
    if(findfield(BananaBunch, SN)==0){
         _tempWK = BananaBunch.WK;
         _tempParcela = BananaBunch.PC;
         BananaBunch.WK=ribbonColor;
         
    }                                                    
    insert(BananaBunch);
    
    if(inSN!=0){
    switch(parcelaNo){
           case 88:
                 ParcelaDB.pID=88;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;
          case 89:
                 ParcelaDB.pID=89;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;             
           case 90:
                 ParcelaDB.pID=90;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;                
           case 91:
                 ParcelaDB.pID=91;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;      
           case 92:
                 ParcelaDB.pID=92;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;
           case 93:
                 ParcelaDB.pID=93;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;
           case 94:
                 ParcelaDB.pID=94;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;
             case 95:
                 ParcelaDB.pID=95;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;
              case 96:
                 ParcelaDB.pID=96;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
                 break;   
           default:
                   infobox("error inserting statistics");
                   break;                 
    }
    
    
    //do minus here
    
    if(parcelaNo==88){           
                 ParcelaDB.pID=88;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
         }else if(parcelaNo==89){
          
                 ParcelaDB.pID=89;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
           }else if(parcelaNo==90){
           
                 ParcelaDB.pID=90;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
           }else if(parcelaNo==91){          
                 ParcelaDB.pID=91;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
            }else if(parcelaNo==92){
          
                 ParcelaDB.pID=92;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
            }else if(parcelaNo==93){           
                 ParcelaDB.pID=93;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
            }else if(parcelaNo==94){

                 ParcelaDB.pID=94;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
             }else if(parcelaNo==95){

                 ParcelaDB.pID=95;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(_tempWK==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7--;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(_tempWK==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8--;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(_tempWK==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9--;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(_tempWK==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10--;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(_tempWK==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11--;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(_tempWK==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12--;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
              }else if(parcelaNo==96){

                 ParcelaDB.pID=96;
                 if(findfield(ParcelaDB,pID)==0){                        
                    if(ribbonColor==7){
                       countAge7 = ParcelaDB.bWeek7;
                       countAge7++;
                       ParcelaDB.bWeek7=countAge7; 
                    }else if(ribbonColor==8){
                       countAge8 = ParcelaDB.bWeek8;
                       countAge8++;
                       ParcelaDB.bWeek8=countAge8;
                    }else if(ribbonColor==9){
                       countAge9 = ParcelaDB.bWeek9;
                       countAge9++;
                       ParcelaDB.bWeek9=countAge9;                            
                    }else if(ribbonColor==10){
                       countAge10 = ParcelaDB.bWeek10;
                       countAge10++;
                       ParcelaDB.bWeek10=countAge10;
                    }else if(ribbonColor==11){
                       countAge11 = ParcelaDB.bWeek11;
                       countAge11++;
                       ParcelaDB.bWeek11=countAge11;
                    }else if(ribbonColor==12){
                       countAge12 = ParcelaDB.bWeek12;
                       countAge12++;
                       ParcelaDB.bWeek12=countAge12;
                    }else { infobox("error saving statistics..");}              
                                              
                 }
                 insert(ParcelaDB);  
             }else {
                   clearscreen();
                   showtext(10,10,_tempParcela);
                   infobox("nothing to deduct : "+_tempParcela);
             }
    
    
    
   } 
    

    
}







void BananaBunchReports(void){

     selectbox("Select Report"){
          "Total and Average Weight"      reportsAveFarm();
          "Min & Max Weight"   reportsMinMaxBunches();
          "Bunch by Week"      reportsBunchesperAge();
     }


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
          "Farm Number"     farmNo until (farmNo>=30 && farmNo<=32 );
          "Parcela Number"  parcelaNo until ( parcelaNo >= 88 && parcelaNo <=96 );
          //"Parcela Number"  parcelaNo until  (farmConditions(farmNo)) ;
          "Lot Number"      lotNo;
          "Gang Number"     gangNo;                    
     }
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
                  
             if(sn==0){
                       LastBananaBunchSetting.SID=1;
                       if(findfield(LastBananaBunchSetting, SID)==0){
                          sn = LastBananaBunchSetting.rvLastTotalBunch;
                          tw = LastBananaBunchSetting.rvLastTotalWeight;
                          
                          avetw = tw/sn;
                       }
             }     

           
            
            weighBananaBunchScreen();    
                   
             
            if((getweight()==0) && (net>minLoad) && issettled){  
                                                                                   
                if (flagUnload){
                        
                         crNet=net;             
                         tw=tw+crNet;                                                                                                                            
                         saveBananaBunchWeigh(crNet, tw);                          
                         clearscreen(); 
                                                
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





void  exportSpreadsheetINTERNAL(void){
      char ch;
      int i;
      int j;
      int xList;
      int yList;

      int _sn;
      decimal _wr%5.1;
      int _wk;
      string _fm[4];
      string _pc[4];
      string _bk[7];
      string _cc[4];
      
     

      
      int _SID;
      int _SN;
      decimal _BC%3.1;
      decimal _FL%3.1;
      decimal _NH%3.1;
      decimal _FC%3.1;
      decimal _HC%3.1;
      string _location[10];

      _location="shared";

      if(fexists(_location+"/TADECO_Banana_Bunch_Data.csv")){
         fremove(_location+"/TADECO_Banana_Bunch_Data.csv");
         formatCSV(_location);         
      }else{
         formatCSV(_location);
      }


      if(fexists(_location+"/TADECO_Banana_Bunch_Sampling.csv")){
         fremove(_location+"/TADECO_Banana_Bunch_Sampling.csv");
         formatSamplingCSV(_location);                                                          
      }else{
         formatSamplingCSV(_location);
      }
      clearscreen();
      savingScreenCSV();
      
         
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
         
         _sn=_sn+1;
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
           _SID=_SID+1;    
               saveBananaSampleCSV(_SID, _SN, _BC, _FL, _NH, _FC, _HC, _location); 
      }

      clearscreen();     
    donesavingScreen();
         
      
      for(;;){
              if(keypressed()){
                ch=readkey();
                
                if(ch==fct6){ 
                              clearscreen();                            
                             break;
                }
              
              }
      
      }
      

}

void  exportSpreadSheetUSB(void){
      int i;
      int j;
      int xList;
      int yList;
      char ch;

      int _sn;
      decimal _wr%5.1;
      int _wk;
      string _fm[4];
      string _pc[4];
      string _bk[7];
      string _cc[4];

     
      
      int _SID;
      int _SN;
      decimal _BC%3.1;
      decimal _FL%3.1;
      decimal _NH%3.1;
      decimal _FC%3.1;
      decimal _HC%3.1;
      string _location[10];

      _location= "usbstick";


      if(fexists(_location+"/TADECO_Banana_Bunch_Data.csv")){
         fremove(_location+"/TADECO_Banana_Bunch_Data.csv");
         formatCSV(_location);         
      }else{
         formatCSV(_location);
      }


      if(fexists(_location+"/TADECO_Banana_Bunch_Sampling.csv")){
         fremove(_location+"/TADECO_Banana_Bunch_Sampling.csv");
         formatSamplingCSV(_location);                                                          
      }else{
         formatSamplingCSV(_location);
      }

       clearscreen();
      savingScreenCSV();       
      
      xList = records(BananaBunch);
      
      for(i=1; i<xList;i++){
               
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
      
      for(j=1; j<yList;j++){
               BananaSampling.SID = j+1;
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

      clearscreen();     
     donesavingScreen();     
      for(;;){
              if(keypressed()){
                ch=readkey();
                
                if(ch==fct6){  
                             clearscreen();                           
                             break;
                }
              
              }
      
      }

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
     fremove("shared/TADECO_Banana_Bunch_Data.csv");
     fremove("shared/TADECO_Banana_Bunch_Sampling.csv");
     
    farmNo="";
    parcelaNo="";
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

void testMemorySpace(void){
     int xx;
     int yy;
     char ch;
     
    clearscreen();
    savingScreenCSV();
    
     for(xx=0;xx<1000;xx++){
          
            
            BananaBunch.SN = xx;
            BananaBunch.WR = 845.6;
            BananaBunch.BK = "XXXXXXX";
            BananaBunch.FM = "XXXX";
            BananaBunch.WK = 9;
            BananaBunch.PC = "XXXX";
            BananaBunch.CC = "XXXX";
            BananaBunch.DATE = date;
            BananaBunch.TIME = time;
            
            if(insert(BananaBunch)==2){
                  infobox("memory full");
                  delay(5);
                  break;
            }else{
            
                  insert(BananaBunch);
                  delay(0.01);
            }
            
            
     }


     

    
    for(yy=0;yy<100;yy++){
     
          
             BananaSampling.SID = yy;
             BananaSampling.SN =yy;
             BananaSampling.BC = 999.9;
             BananaSampling.FL = 999.9;
             BananaSampling.NH = 999.9;
             BananaSampling.FC = 999.9;
             BananaSampling.HC = 999.9;             
             
                
             
               if(insert(BananaSampling)==2){
                  infobox("memory full");
                  delay(5);
                  break;
            }else{
            
                  insert(BananaSampling); 
                  delay(0.01);
            }
                                  
     }
     
     clearscreen();
      background(255);
     donesavingScreen();
     
     
     for(;;){
              if(keypressed()){
                 ch=readkey();
                 if(ch==fct6){
                     
                     
                     break;         
                 }            
                 
             }
     }

}


void testcheckmemoryspace(void){
     char ch;
     int numrec;
     clearscreen();
     
     numrec = records(BananaBunch);
     
     showtext(10,10,adj(numrec,5,0));
     



     for(;;){
              if(keypressed()){
                 ch=readkey();
                 if(ch==fct6){
                     
                     
                     break;         
                 }            
                 
             }
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
                "Test Memory"                        testMemorySpace();
                "Test check memory space"            testcheckmemoryspace();
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
     selectbox("Main Menu                        IT-6000E - TADECO"){
       "Banana Weighing"    WeighingMode();
       "Banana Weighing Settings" bananaWeighingSetting();
       "Supervisor Mode" supervisorMode();
       
     } 
   }  
}
