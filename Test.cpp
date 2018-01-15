#include <nana/gui.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
int main()
{
	using namspace nana;
	form fm;
	
	fm.show();
	
	internationalization i18n;
	//Translate these 2 words into Chinese.
	i18n.set("OK", L"确定");
	i18n.set("Cancel", L"取消");
		
	//Show an inputbox when the form is clicked.
	fm.events().click([&fm]
	{
		inputbox::text name(L"<bold blue>Name</>", L"Nana C++ Library");	//The format text is also available, the second parameter can be given for default value.
		inputbox::text gender(L"Gender", {L"Male", L"Female"});
		inputbox::date birth(L"Date of birth");
		inputbox::real height(L"Height(cm)", 100, 1, 300, 1);
		inputbox::integer kids(L"Kids", 0, 0, 100, 1);
		
		inputbox inbox(fm, L"Please input <bold>your personal information</>.", L"Personal information");
		
		//Open the image file
		paint::image img(L"inputbox.bmp");
		
		//Use 'copy' to assign the image, these image objects refer to the same
		//image resource.
		inbox.image(img, true, { 380, 0, 40, 100 });
		inbox.image(img, false, { 420, 0, 40, 100 });
		inbox.image_v(img, true, { 0, 0, 380, 50 });
		inbox.image_v(img, false, { 0, 50, 380, 50 });
		
		//Sets a verifier
		inbox.verify([&name](window handle)
		{
			if (name.value().empty())
			{
				msgbox mb(handle, L"Invalid input");
				mb << L"Name should not be empty, Please input your name.";
				mb.show();
				return false; //verification failed
			}
			return true; //verified successfully
		});
		
		if(inbox.show(name, gender, birth, height, kids))
		{
			auto n = name.value();		//nana::string
			auto g = gender.value();	//nana::string
			auto b = birth.value();		//nana::string
			auto year = birth.year();	//int
			auto month = birth.month(); //int
			auto day = birth.day();		//int
			auto h = height.value();	//double
			auto k = kids.value();		//int
		}
	});
	
	exec();
}