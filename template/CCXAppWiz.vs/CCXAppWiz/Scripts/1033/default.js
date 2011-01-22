function OnFinish(selProj, selObj) {
    try {
        var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
        var strProjectName = wizard.FindSymbol('PROJECT_NAME');

        //         var WizardVersion = wizard.FindSymbol('WIZARD_VERSION');
        //         if(WizardVersion >= 8.0)
        //         {
        //         }

        // Create symbols based on the project name
        var strSafeProjectName = CreateSafeName(strProjectName);
        wizard.AddSymbol("SAFE_PROJECT_NAME", strSafeProjectName);
        wizard.AddSymbol("NICE_SAFE_PROJECT_NAME", strSafeProjectName.substr(0, 1).toUpperCase() + strSafeProjectName.substr(1))
        wizard.AddSymbol("UPPERCASE_SAFE_PROJECT_NAME", strSafeProjectName.toUpperCase());

        // Set current year symbol
        var d = new Date();
        var nYear = 0;
        nYear = d.getFullYear();
        if (nYear >= 2003)
            wizard.AddSymbol("CCX_CURRENT_YEAR", nYear);
        // Create project and configurations
        selProj = CreateCustomProject(strProjectName, strProjectPath);
        AddConfigurations(selProj, strProjectName);
        AddFilters(selProj);

        var InfFile = CreateCustomInfFile();
        AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
        AddPchSettings(selProj);
        InfFile.Delete();

        selProj.Object.Save();

    }
    catch (e) {
        if (e.description.length != 0)
            SetErrorInfo(e);
        return e.number;
    }
}

function CreateCustomProject(strProjectName, strProjectPath) {
    try {
        var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
        var strProjTemplate = '';
        strProjTemplate = strProjTemplatePath + '\\default.vcproj';

        var Solution = dte.Solution;
        var strSolutionName = "";
        if (wizard.FindSymbol("CLOSE_SOLUTION")) {
            Solution.Close();
            strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
            if (strSolutionName.length) {
                var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
                Solution.Create(strSolutionPath, strSolutionName);
            }
        }

        // Create vcproj.user file
        var FileSys = new ActiveXObject("Scripting.FileSystemObject");
        var strUserTarget = strProjectName + ".win32.vcproj.user";
        var strUserPath = FileSys.BuildPath(strProjectPath, strUserTarget);
        
        var astrParentPath = new Array();
        astrParentPath[0] = strProjectPath;
        while (astrParentPath.length) {
            var strPath = astrParentPath.pop();
            var strParentPath = FileSys.GetParentFolderName(strPath);

            if (!FileSys.FolderExists(strParentPath)) {
                astrParentPath.push(strPath);
                astrParentPath.push(strParentPath);
                continue;
            }
            else {
                FileSys.CreateFolder(strPath);
            }
        }

        var file = FileSys.OpenTextFile(strUserPath, 2, true);
        var strUserValue = "<?xml version=\"1.0\" encoding=\"utf-8\"?><VisualStudioUserFile ProjectType=\"Visual C++\" Version=\"9.00\" ShowAllFiles=\"true\"></VisualStudioUserFile>";
        file.WriteLine(strUserValue);
        file.Close();

        var strProjectNameWithExt = '';
        strProjectNameWithExt = strProjectName + '.win32.vcproj';

        var oTarget = wizard.FindSymbol("TARGET");
        var prj;
        if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
        {
            var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
            prj = prjItem.SubProject;
        }
        else {
            prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
        }
        return prj;
    }
    catch (e) {
        throw e;
    }
}

function AddFilters(proj) {
    try {
        // Add the folders to your project
        var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
        var group = proj.Object.AddFilter('source');
        group.Filter = strSrcFilter;

        strSrcFilter = wizard.FindSymbol('INCLUDE_FILTER');
        group = proj.Object.AddFilter('include');
        group.Filter = strSrcFilter;

        strSrcFilter = wizard.FindSymbol('RESOURCE_FILTER');
        group = proj.Object.AddFilter('resource');
        group.Filter = strSrcFilter;
    }
    catch (e) {
        throw e;
    }
}


// Configurations data
var nNumConfigs = 2;

var astrConfigName = new Array();
astrConfigName[0] = "Debug";
astrConfigName[1] = "Release";

function AddConfigurations(proj, strProjectName) {
    try {
        var nCntr;
        for (nCntr = 0; nCntr < nNumConfigs; nCntr++) {
            // Check if it's Debug configuration
            var bDebug = false;
            if (astrConfigName[nCntr].search("Debug") != -1)
                bDebug = true;

            // General settings
            var config = proj.Object.Configurations(astrConfigName[nCntr]);

            //             if(wizard.FindSymbol("CCX_USE_UNICODE"))
            config.CharacterSet = charSetUnicode;
            //             else
            //                config.CharacterSet = charSetMBCS;

            config.OutputDirectory = '$(SolutionDir)$(ConfigurationName).win32'
            config.IntermediateDirectory = '$(ConfigurationName).win32';

            // Compiler settings
            var CLTool = config.Tools('VCCLCompilerTool');

            // Additional Inlcude Directories
            var strAddIncludeDir = '.;.\\win32;.\\Classes';
            strAddIncludeDir += ';..\\cocos2dx;..\\cocos2dx\\include';
            strAddIncludeDir += ';..\\platform_support\\include;..\\platform_support\\third_party\\win32\\OGLES';
            
            if (wizard.FindSymbol('CCX_USE_BOX2D')) {
                strAddIncludeDir += ';..\\;..\\Box2D';
            }
            if (wizard.FindSymbol('CCX_USE_CHIPMUNK')) {
                strAddIncludeDir += ';..\\chipmunk\\include\\chipmunk';
            }
            if (wizard.FindSymbol('CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE')) {
                strAddIncludeDir += ';..\\CocosDenshion\\Include';
            }
            CLTool.AdditionalIncludeDirectories = strAddIncludeDir;

            CLTool.UsePrecompiledHeader = pchNone;  // pchUseUsingSpecific;
            CLTool.WarningLevel = warningLevel_3;
            if (bDebug) {
                CLTool.RuntimeLibrary = rtMultiThreadedDebug;
                CLTool.MinimalRebuild = true;
                CLTool.DebugInformationFormat = debugEditAndContinue;
                CLTool.BasicRuntimeChecks = runtimeBasicCheckAll;
                CLTool.Optimization = optimizeDisabled;
            }
            else {
                CLTool.RuntimeLibrary = rtMultiThreaded;
                CLTool.ExceptionHandling = false;
                CLTool.DebugInformationFormat = debugDisabled;
            }

            var strDefines = GetPlatformDefine(config);
            strDefines += "_WINDOWS;STRICT;";
            if (bDebug)
                strDefines += "_DEBUG;COCOS2D_DEBUG=1";
            else
                strDefines += "NDEBUG";
            CLTool.PreprocessorDefinitions = strDefines;

            // Disable special warning
            CLTool.DisableSpecificWarnings = "4251";

            // Linker settings
            var LinkTool = config.Tools('VCLinkerTool');
            LinkTool.SubSystem = subSystemWindows;
            LinkTool.TargetMachine = machineX86;
            if (bDebug) {
                LinkTool.LinkIncremental = linkIncrementalYes;
                LinkTool.GenerateDebugInformation = true;
            }
            else {
                LinkTool.LinkIncremental = linkIncrementalNo;
            }

            // Additional Library Directories
            var strAddDepends = 'libcocos2d.lib libgles_cm.lib';
            if (wizard.FindSymbol('CCX_USE_BOX2D')) {
                strAddDepends += ' libBox2d.lib';
            }
            if (wizard.FindSymbol('CCX_USE_CHIPMUNK')) {
                strAddDepends += ' libchipmunk.lib';
            }
            if (wizard.FindSymbol('CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE')) {
                strAddDepends += ' libCocosDenshion.lib';
            }
            LinkTool.AdditionalLibraryDirectories = '$(OutDir)';
            LinkTool.AdditionalDependencies = strAddDepends;

            // Resource settings
            var RCTool = config.Tools("VCResourceCompilerTool");
            RCTool.Culture = rcEnglishUS;
            RCTool.AdditionalIncludeDirectories = "$(IntDir)";
            if (bDebug)
                RCTool.PreprocessorDefinitions = "_DEBUG";
            else
                RCTool.PreprocessorDefinitions = "NDEBUG";

            // MIDL settings
            var MidlTool = config.Tools("VCMidlTool");
            MidlTool.MkTypLibCompatible = false;
            if (IsPlatformWin32(config))
                MidlTool.TargetEnvironment = midlTargetWin32;
            if (bDebug)
                MidlTool.PreprocessorDefinitions = "_DEBUG";
            else
                MidlTool.PreprocessorDefinitions = "NDEBUG";
            MidlTool.HeaderFileName = strProjectName + ".h";
            MidlTool.InterfaceIdentifierFileName = strProjectName + "_i.c";
            MidlTool.ProxyFileName = strProjectName + "_p.c";
            MidlTool.GenerateStublessProxies = true;
            MidlTool.TypeLibraryName = "$(IntDir)/" + strProjectName + ".tlb";
            MidlTool.DLLDataFileName = "";

            // Post-build settings
            var PostBuildTool = config.Tools("VCPostBuildEventTool");
            PostBuildTool.Description = "Performing copy resource from Resource to OutDir...";
            PostBuildTool.CommandLine = "copy /Y \"$(ProjectDir)Resource\\*.*\" \"$(OutDir)\"";
        }
    }
    catch (e) {
        throw e;
    }
}

function AddPchSettings(proj) {
    try {
        //         var files = proj.Object.Files;
        //         var fStdafx = files("StdAfx.cpp");
        // 
        //         var nCntr;
        //         for(nCntr = 0; nCntr < nNumConfigs; nCntr++)
        //         {
        //             var config = fStdafx.FileConfigurations(astrConfigName[nCntr]);
        //             config.Tool.UsePrecompiledHeader = pchCreateUsingSpecific;
        //         }
    }
    catch (e) {
        throw e;
    }
}

function DelFile(fso, strWizTempFile) {
    try {
        if (fso.FileExists(strWizTempFile)) {
            var tmpFile = fso.GetFile(strWizTempFile);
            tmpFile.Delete();
        }
    }
    catch (e) {
        throw e;
    }
}

function CreateCustomInfFile() {
    try {
        var fso, TemplatesFolder, TemplateFiles, strTemplate;
        fso = new ActiveXObject('Scripting.FileSystemObject');

        var TemporaryFolder = 2;
        var tfolder = fso.GetSpecialFolder(TemporaryFolder);

        var strWizTempFile = tfolder.Path + "\\" + fso.GetTempName();

        var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
        var strInfFile = strTemplatePath + '\\Templates.inf';
        wizard.RenderTemplate(strInfFile, strWizTempFile);

        var WizTempFile = fso.GetFile(strWizTempFile);

        return WizTempFile;
    }
    catch (e) {
        throw e;
    }
}

function GetTargetName(strName, strProjectName) {
    try {
        var strTarget = strName;

        var nIndex = strName.indexOf("root");

        if (nIndex >= 0) {
            strTarget = strName.substring(0, nIndex) + strProjectName + strName.substring(nIndex + 4, strName.length);
        }

        return strTarget;
    }
    catch (e) {
        throw e;
    }
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile) {
    try {
        var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

        var strTpl = '';
        var strName = '';

        var strTextStream = InfFile.OpenAsTextStream(1, -2);
        while (!strTextStream.AtEndOfStream) {
            strTpl = strTextStream.ReadLine();
            if (strTpl != '') {
                strName = strTpl;
                var strTarget = GetTargetName(strName, strProjectName);
                var strTemplate = strTemplatePath + '\\' + strTpl;
                var strFile = strProjectPath + '\\' + strTarget;

                var bCopyOnly = true;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
                var strExt = strName.substr(strName.lastIndexOf("."));
                if (strExt == ".h" || strExt == ".cpp" || strExt == ".c" || strExt == ".rc")
                    bCopyOnly = false;
                wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);

                // don't add these files to the project
                if (strTarget == strProjectName + ".h" ||
                   strTarget == strProjectName + "ps.mk" ||
                   strTarget == strProjectName + "ps.def")
                    continue;

                proj.Object.AddFile(strFile);
            }
        }
        strTextStream.Close();
    }
    catch (e) {
        throw e;
    }
}
