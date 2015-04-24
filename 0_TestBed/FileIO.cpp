/* Project: BITCHIN PONG */
/* Team Members: Kirk Hewitt, Jordan Karlsruher, John Radkins */
/* DSA II - 309.02 */
/* Spring 2015 */

#include "GameManager.h"

/* ReadConfig */
void GameManager::ReadConfig()
{
	//If we are reading the changes the changes, know what file to open
	String sRoot = systemSingleton->m_pFolder->GetFolderRoot();
	String App = systemSingleton->ApplicationName;
	App = sRoot + App + ".cfg";

	FileReaderClass reader;
	//If the file doesnt exist, create it and exit this method
	if(reader.ReadFile(App.c_str()) == MEErrors::ERROR_FILE_MISSING)
	{
		WriteConfig();
		return;
	}
	
	//read the file
	reader.Rewind();
	while(reader.ReadNextLine() == RUNNING)
	{
		String sWord = reader.GetFirstWord();

		int nLenght  = reader.m_sLine.length();
		char* zsTemp = new char[nLenght];
		
		if(sWord == "Fullscreen:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
			if(nValue == 0)
				systemSingleton->SetWindowFullscreen(false);
			else
				systemSingleton->SetWindowFullscreen(true);
		}
		else if(sWord == "Borderless:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
			if(nValue == 0)
				systemSingleton->SetWindowBorderless(false);
			else
				systemSingleton->SetWindowBorderless(true);
		}
		else if(sWord == "Resolution:")
		{
			int nValue1;
			int nValue2;
			sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1,  &nValue2);
			systemSingleton->WindowWidth = nValue1;
			systemSingleton->WindowHeight = nValue2;
		}
		else if(sWord == "Ambient:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
			lightManagerSingleton->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
		}
		else if(sWord == "Background:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			float fValueW;
			sscanf_s(reader.m_sLine.c_str(), "Background: [%f,%f,%f,%f]", &fValueX, &fValueY, &fValueZ, &fValueW);
			windowColor = vector4(fValueX, fValueY, fValueZ, fValueW);
		}
		else if(sWord == "AmbientPower:")
		{
			float fValue;
			sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
			lightManagerSingleton->SetIntensity(fValue, 0);
		}
		else if(sWord == "Data:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderData( zsTemp );
		}
		else if(sWord == "3DS:")
		{
			sscanf_s(reader.m_sLine.c_str(), "3DS: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderM3DS( zsTemp );
		}
		else if(sWord == "BTO:")
		{
			sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMBTO( zsTemp );
		}
		else if(sWord == "FBX:")
		{
			sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMFBX( zsTemp );
		}
		else if(sWord == "OBJ:")
		{
			sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMOBJ( zsTemp );
		}
		else if(sWord == "POM:")
		{
			sscanf_s(reader.m_sLine.c_str(), "POM: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderMPOM( zsTemp );
		}
		else if(sWord == "Level:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderLVL( zsTemp );
		}
		else if(sWord == "Textures:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
			systemSingleton->m_pFolder->SetFolderTextures( zsTemp );
		}

		delete[] zsTemp;
		zsTemp = nullptr;
	}
	reader.CloseFile();
}

/* WriteConfig */
void GameManager::WriteConfig()
{
	// Write the configuration for this application
	String sRoot = systemSingleton->m_pFolder->GetFolderRoot();
	String App = systemSingleton->ApplicationName;
	App = sRoot + App + ".cfg";

	FILE *pFile; 
	fopen_s(&pFile, App.c_str(),"w");
	if(!pFile)	//If we couldn't create the file we exit without changes.
		return;

	rewind(pFile);
	fprintf(pFile,"# Configuration file for the program: %s", systemSingleton->GetAppName().c_str());
	
	fprintf(pFile,"\n\nFullscreen: ");
	if(systemSingleton->IsWindowFullscreen())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nBorderless: ");
	if(systemSingleton->IsWindowBorderless())
		fprintf(pFile,"1");
	else
		fprintf(pFile,"0");

	fprintf(pFile,"\nContext: OPENGL3X"); //Only openGL3X context is supported ATM

	fprintf(pFile,"\n\n# Resolution: [ 640 x 480 ]");
	fprintf(pFile,"\n# Resolution: [ 1280 x 720 ]");
	fprintf(pFile,"\n# Resolution: [ 1680 x 1050 ]");
	fprintf(pFile,"\n# Resolution: [ 1920 x 1080 ]");
	fprintf(pFile,"\n# Resolution: [ 2650 x 1440 ]");
	fprintf(pFile,"\nResolution: [ %d x %d ]", systemSingleton->WindowWidth, systemSingleton->WindowHeight);

	fprintf(pFile,"\n\nAmbient: [%.2f,%.2f,%.2f]",
		lightManagerSingleton->GetColor(0).r, lightManagerSingleton->GetColor(0).g, lightManagerSingleton->GetColor(0).b);
	fprintf(pFile,"\nAmbientPower: %.2f", lightManagerSingleton->GetIntensity(0));

	fprintf(pFile,"\n\nBackground: [%.3f,%.3f,%.3f,%.3f]",
		windowColor.r, windowColor.g, windowColor.b, windowColor.a);

	fprintf(pFile,"\n\n# Folders:");
	
	fprintf(pFile,"\nData:		%s", systemSingleton->m_pFolder->GetFolderData().c_str());
	fprintf(pFile,"\n3DS:		%s", systemSingleton->m_pFolder->GetFolderM3DS().c_str());
	fprintf(pFile,"\nBTO:		%s", systemSingleton->m_pFolder->GetFolderMBTO().c_str());
	fprintf(pFile,"\nFBX:		%s", systemSingleton->m_pFolder->GetFolderMFBX().c_str());
	fprintf(pFile,"\nOBJ:		%s", systemSingleton->m_pFolder->GetFolderMOBJ().c_str());
	fprintf(pFile,"\nLevel:		%s", systemSingleton->m_pFolder->GetFolderLVL().c_str());
	fprintf(pFile,"\nTextures:	%s", systemSingleton->m_pFolder->GetFolderTextures().c_str());

	fclose(pFile);
}