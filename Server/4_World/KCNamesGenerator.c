#ifndef KUBC_NAME_GENERATOR
/// @brief Настройка имен с вероятностью выпадения
class KCNamesGenerator
{

    private ref TStringFloatMap options;

    private ref TFloatArray cumulativeWeights;

    private float currentWeight;

    void KCNamesGenerator(TStringFloatMap sett)
    {
        options = sett;
        cumulativeWeights = new TFloatArray();
        currentWeight = 0;
        cumulativeWeights.Insert(currentWeight);
        for(int i=0; i< options.Count(); i++)
        {
            currentWeight += options.GetElement(i);
            cumulativeWeights.Insert(currentWeight);
        }
    }

    string GetRandomName()
    {
        int index = FindIndex(Math.RandomFloat(0, currentWeight));
        return options.GetKey(index);
    }

    private int FindIndex(float r)
    {
        for(int i=0; i< cumulativeWeights.Count() - 1; i++)
        {
            if (r >= cumulativeWeights.Get(i))
            {
                if (r < cumulativeWeights.Get(i+1))
                {
                    return i;
                }
            }
        }
        return options.Count() - 1;
    } 
}
#define KUBC_NAME_GENERATOR
#endif