void saveBananaBunchCSV(int _sn, decimal _wr, int _wk, string _fm, string _pc, string _bk, string _cc, string _xlocation){
     fopen(0,_xlocation+"/TADECO_Banana_Bunch_Data.csv");
     csvbuffer= concat(  _sn,"," , _wr,",", _wk,"," , _fm,",", _pc,",",  _bk,",", _cc,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
    fclose(0);
}

void saveBananaSampleCSV(int _SID, int _SN, decimal _BC, decimal _FL, decimal _NH, decimal _FC, decimal _HC, string _xlocation){
     fopen(0,_xlocation+"/TADECO_Banana_Bunch_Sampling.csv");
     csvbuffer= concat(  _SID,"," , _SN,",", _BC,"," , _FL,",", _NH,",",  _FC,",", _HC,"\r\n");            
             if(fwrite(0,csvbuffer,length(csvbuffer)) != length(csvbuffer)){ infobox("error writing file");} 
    fclose(0);
}