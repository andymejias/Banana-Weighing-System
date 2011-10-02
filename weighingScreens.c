
void weighBananaBunchScreen(void){
  
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

void reportFarmScreen(void){

     begindraw();
     font(16);
     fontsize(11);     
     
     fctinfo(1,lsub("Farm 30"));    
     fctinfo(2,lsub("Farm 31"));    
     fctinfo(3,lsub("Farm 32"));    
     fctinfo(6,lsub("Exit"));    
    
     
     showtext(5,5,"Farm No");
          
     showtext(100,5,"Total:");
     showtext(200,5,"Ave:");     
          
          
     posto(10,20);
     boxto(300,120,14);
     posto(10,45);
     lineto(299,45);
     posto(10,70);
     lineto(299,70);
     posto(10,95);
     lineto(299,95);
     posto(85,20);
     lineto(85,119);
     posto(185,20);
     lineto(185,119);
     
     
     showtext(15,25,"Parcela No.");
     showtext(100,25,"Total Bunch");
     showtext(200,25,"Ave. Weight");
     
     enddraw();


}

void reportParcelaMinMaxScreen(void){

     begindraw();
     font(16);
     fontsize(11);     
     
     fctinfo(1,lsub("Farm 30"));    
     fctinfo(2,lsub("Farm 31"));    
     fctinfo(3,lsub("Farm 32"));    
     fctinfo(6,lsub("Exit"));    
    
     
     showtext(5,5,"Farm No");
          
     posto(10,20);
     boxto(300,120,14);
     posto(10,45);
     lineto(299,45);
     posto(10,70);
     lineto(299,70);
     posto(10,95);
     lineto(299,95);
     posto(85,20);
     lineto(85,119);
     posto(185,20);
     lineto(185,119);
     
     
     showtext(15,25,"Parcela No.");
     showtext(90,25,"Min Bunch Weight");
     showtext(200,25,"Max Bunch Weight");
     
     enddraw();


}


void reportBunchesperAgeScreen(void){

     begindraw();


     fctinfo(1,lsub("Farm 3"));    
     fctinfo(2,lsub("Farm 4"));    
     fctinfo(3,lsub("Farm 5"));    
     fctinfo(6,lsub("Exit")); 

     showtext(5,5,"Farm No");

     posto(5,20);
     boxto(312,125,14);
     posto(10,45);
     lineto(309,45);
     posto(10,70);
     lineto(309,70);
     posto(10,95);
     lineto(309,95);
     //
      posto(55,20);
     lineto(55,124);
      posto(97,20);
     lineto(97,124);
      posto(139,20);
     lineto(139,124);
      posto(181,20);
     lineto(181,124);
      posto(223,20);
     lineto(223,124);
     posto(265,20);
     lineto(265,124);


     showtext(75,30,"7");
     showtext(120,30,"8");
     showtext(157,30,"9");
     showtext(200,30,"10");
     showtext(240,30,"11");
     showtext(282,30,"12");


     enddraw();
}


void savingScreenCSV(void){
     clearscreen();
      begindraw();
      fctinfo(6,lsub("Exit"));

      posto(20,40);
      background(88); 
      boxto(290,80,14);

      font(16);
      fontsize(14);
      foreground(95);       
      showtext(40,50,"Saving... do not turn off unit!");   
      


      enddraw();

}

void donesavingScreen(void){
     clearscreen();
     fctinfo(6,lsub("Exit"));
    
    
      begindraw();
      
      
      posto(20,40);
      background(230); 
      boxto(290,80,14);


       font(16);
       fontsize(14);
       foreground(56);       
       showtext(40,50,"Done saving... you can turn off machine.");


      enddraw();


}
