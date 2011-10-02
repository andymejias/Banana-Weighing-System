
void formatCSV(string __xlocation){    

       fopen(0,__xlocation+"/TADECO_Banana_Bunch_Data.csv");       
       csvbuffer= concat("Data from Packing Station 2 Banana Bunch Weighing Unit","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("TADECO Inc.","\r\n");       
      
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("Date: "+dateFormat(formatDate) ,"\r\n");   
        
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}
       csvbuffer= concat("SN,","WR,","WK,","FM,","PC,","BK,","CC," ,"\r\n"); 
                           
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}                 
       fclose(0);
}

void formatSamplingCSV(string __xlocation){    
       fopen(0,__xlocation+"/TADECO_Banana_Bunch_Sampling.csv");       
       csvbuffer= concat("Sampling Data from Packing Station 2 Banana Bunch Weighing Unit","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("TADECO INC","\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
       csvbuffer= concat("Date: "+dateFormat(formatDate)+";" ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}
       csvbuffer= concat("SID,","SN,","BC,","FL,","NH,","FC,","HC," ,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");}                 
       fclose(0);
}