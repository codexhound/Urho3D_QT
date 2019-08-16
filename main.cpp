#include <QtPlugin>
#include "UniQApp.h"
#include <Urho3D/Core/Context.h>
#include <Urho3D/Container/Ptr.h>
#include "WindowMain.h"
#include <iostream>

int main(int argc, char *argv[])
{
	//initialize rand
	srand(static_cast<int>(time(0))); 

    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin) //build app for windows

    Context context;
    UniQApp app(&context,argc,argv);
	
    return app.Run();
}
