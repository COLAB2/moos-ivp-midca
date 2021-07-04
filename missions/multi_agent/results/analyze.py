import pandas as pd
import matplotlib.pyplot as plt
#def readDataFrame(filename="grace.csv"):
#    subset_results = pd.read_csv(filename)
#    return subset_results

def top_hotspots(s):
    return s[ s['Hotspots(#)'] == s['Hotspots(#)'].max() ]


results = pd.read_csv("grace.csv")
results_baseline = pd.read_csv("graceOld.csv")
results = results.set_index('index')
results_baseline = results_baseline.set_index('index')
#SurveyedGoals(Positions)
subset_results = results.groupby(['index']).agg(["max", "mean"])
subset_baseline = results_baseline.groupby(['index']).agg(["max", "mean"])

subset_results.columns = ["_".join(x) for x in subset_results.columns.ravel()]
subset_baseline.columns = ["_random_".join(x) for x in subset_baseline.columns.ravel()]

total_results = pd.merge(subset_results, subset_baseline, on="index")
#print (subset_results.info)
total_results["SurveyedGoals(#)_Perecent"] = (total_results["SurveyedGoals(#)_max"]/25) *100
total_results["SurveyedGoals(#)_random_Percent"] = (total_results["SurveyedGoals(#)_random_max"]/25) *100

#total_results.plot.bar(y=['SurveyedGoals(#)_max' , 'SurveyedGoals(#)_random_max'], stacked=False, rot=0)
total_results.plot.bar(y=['SurveyedGoals(#)_Perecent' , 'SurveyedGoals(#)_random_Percent'], stacked=False, rot=0)
#subset_baseline.plot.bar(y='SurveyedGoals(#)_baseline_max', color = 'g', ax=ax1, stacked=False)
#plt.show()
total_results.to_csv("analysis.csv")
