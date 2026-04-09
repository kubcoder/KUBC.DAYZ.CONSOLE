class KCUserCmdAgent : KCUserCMD
{
    static const string CMD_NAME = "agent";

    const string ARG_ADD = "add";

    const string ARG_LIST = "list";

    override string GetName()
    {
        return KCUserCmdAgent.CMD_NAME;
    }

    private ref map<int, string> agentNames;

    void KCUserCmdAgent()
    {
        map<int, ref AgentBase> m_AgentList = PluginTransmissionAgents.m_AgentList;
        agentNames = new map<int, string>();
        for (int i=0; i<m_AgentList.Count();i++)
        {
            string displayName = m_AgentList.GetKey(i).ToString() + ":" + m_AgentList.GetElement(i).ClassName();
            agentNames.Insert(m_AgentList.GetKey(i), m_AgentList.GetElement(i).ClassName());
            Log(displayName);
        }
    }

    private string GetName(int key)
    {
        if (agentNames.Contains(key))
        {
            return agentNames.Get(key);
        }
        return key.ToString();
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            return true;
        }
        switch (data.Arg[0])
        {
            case ARG_LIST:
                if(data.GetTarget().m_AgentPool.m_VirusPool)
                {
                    if (data.GetTarget().m_AgentPool.m_VirusPool.Count()>0)
                    {
                        for(int j = 0; j < data.GetTarget().m_AgentPool.m_VirusPool.Count(); j++)
                        {
                            data.MessageOwner(GetName(data.GetTarget().m_AgentPool.m_VirusPool.GetKey(j)) + ":" + data.GetTarget().m_AgentPool.m_VirusPool.GetElement(j).ToString());                             
                        }
                        return true;
                    }
                    
                }
                data.MessageOwner("Агентов болезней не найдено");
                break;
            case ARG_ADD:
                if(data.Arg.Count()>2)
                {
                    int aID = data.Arg[1].ToInt();
                    float aCount = data.Arg[2].ToFloat();
                    data.GetTarget().InsertAgent(aID, aCount);
                    data.MessageOwner("Вкатили " + aID + " в количестве " + aCount);
                }
                break;
        }
        return true;
    }
}