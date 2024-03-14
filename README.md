  About Project
------------------------------
  The goal of this project is to write a C++ code that can manage ECG signal data (used data has been provided).
  The code recieves the names of the CSV files that contain the data, finds the BPM values, classifies the heart 
  rhythms, writes this information into seperate text files for each heart rhythm of each patient and finally, 
  merges these categorized signals across patients into combined files per heart rhythm. The project was a group 
  effort between Bulut Demir, Umut Boray Demir, Mehmet Dündar, Zeynep Sude İmdat and Alperen Melih Göncü.
  
  How the Program Runs:
------------------------------
  The code reads ECG signal data from multiple CSV files, records the values of each of the pulses that were read 
  from the files into a Pulse object, collects these objects into a linked list data structure that is named Signal, 
  creates a different linked list for each patient, adds these linked lists to a vector, analyzes the data in these 
  linked lists to classify the heart rhythms (as Tachycardia, Bradycardia or Normal) and organizes this information 
  into separate text files for each heart rhythm of each patient. Additionally, it merges these categorized signals 
  across patients into combined files per heart rhythm for further analysis or reporting.
