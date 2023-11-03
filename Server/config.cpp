class CfgPatches
{
	class EraChat
	{
		units[]= {};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]= {"DZ_Characters"};
	};
};
class CfgMods 
{
	class EraChat
	{
		name = "KUBC.DAYZ.CONSOLE";
		author = "kot23rus";
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