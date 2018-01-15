	#include <nana/gui.hpp>
	#include <iostream>
	#include "LabelPrinter.h"
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <cstdlib>
    #include <nana/gui/widgets/label.hpp>
    #include <nana/gui/widgets/button.hpp>





   
int main(){
    using namespace nana;
    form fm;
    fm.caption(("Rysta LabelPrinter"));
        
        
        fm.show();
        nana::paint::image img("icon.bmp");
        drawing dw(fm);
	    dw.draw([&img](nana::paint::graphics & graph)
	    {
	            if (img.empty()) return;
	            img.paste(graph, nana::point{} );
	    });

	    
        //Show an inputbox when the form is clicked.
        fm.events().click([&fm]
        {

        
			    inputbox::text devID("<bold blue>DevID     </>","");
			    inputbox::text password("<bold blue>Password</>");   
                inputbox::text MAC("<bold blue>MAC        </>"); 
			    inputbox::text modelName("<bold blue>ModelN.  </>","Rysta Multisense");   
			    inputbox::text ID("<bold blue>Panel ID  </>","001");   
                inputbox::text IP("<bold blue>Printer IP </>","192.168.0.109");   
			    inputbox::text port("<bold blue>PrinterPo.</>","44444");  

			    
			    inputbox inbox(fm, "Please enter label data</>.", "Label printer");

   				if(inbox.show(devID,  password,MAC, modelName, ID, IP, port))
                {
                	// This is executed on presing "OK"
                        auto dev = devID.value();
                        auto pw = password.value(); 
                        auto mac = MAC.value();          //nana::string
                        auto model = modelName.value();        //nana::string                               
                        auto id = ID.value();
                        auto ip = IP.value();
                        auto po = port.value();
                        int port = std::stoi(po); 

                        
                        // print a label - code here
                        LabelPrinter printer;
                        int success =printer.print( dev, mac, model, id, pw, ip, port);


                        if( success == 0 ) {
                        	// Erfolg anzeigen....

                        	    using namespace nana;

							    form fm;

							    label lab{fm, "<bold blue size=16>Payload send success!</>"};
							    lab.format(true);

					            button btn{fm, "Quit"};
							    btn.events().click([&fm]{
							    fm.close();
							    });

							    //Layout management
							    fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
							    fm["text"]<<lab;
							    fm["button"] << btn;
							    fm.collocate();
								
							    //Show the form
							    fm.show();

							    //Start to event loop process, it blocks until the form is closed.
							    exec();


                        }else {
                        	// Misserfolg anzeigen..
                        	
                        	    using namespace nana;

							    form fm;

							    label lab{fm, "<bold blue size=14>send failed, try again!</>"};
							    lab.format(true);

					            button btn{fm, "Quit"};
							    btn.events().click([&fm]{
							    fm.close();
							    });

							    //Layout management
							    fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
							    fm["text"]<<lab;
							    fm["button"] << btn;
							    fm.collocate();
								
							    //Show the form
							    fm.show();

							    //Start to event loop process, it blocks until the form is closed.
							    exec();

                        }

		
                }
           });
        
        exec();
}  

