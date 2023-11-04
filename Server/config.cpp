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
		version = 2.0;
		type = "mod";
		class defs 
		{
			class worldScriptModule {
				value = "";
				files[] = {"KUBC.DAYZ.CONSOLE\Server\4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"KUBC.DAYZ.CONSOLE\Server\5_Mission"};
			};
		}; 
	};
};