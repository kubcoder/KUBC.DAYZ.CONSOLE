class CfgPatches
{
	class KUBCconsole
	{
		units[]= {};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]= {"DZ_Characters"};
	};
};
class CfgMods 
{
	class KUBCconsole
	{
		name = "KUBC.DAYZ.CONSOLE";
		author = "kubcoder";
		version = 2.1;
		type = "mod";
		class defs 
		{
			class worldScriptModule {
				value = "";
				files[] = {"KUBC.DAYZ.CONSOLE\4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"KUBC.DAYZ.CONSOLE\5_Mission"};
			};
		}; 
	};
};