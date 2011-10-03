
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
