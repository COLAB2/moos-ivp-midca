import csv

filename = "scores.csv"
midca_filename = "/Users/sravyakondrakunta/Documents/git/midca/midca/examples/agent.txt"
results_filename = "/Users/sravyakondrakunta/Documents/git/midca/midca/examples/results.csv"

no_of_ships = 6
ships_survived = []
score_received = []
deadline = []
def calculate_scores():
    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        score = 0
        lock = 0
        line_count = 1
        for row in csv_reader:
            if lock == 0 and row[0] == "" and line_count != 1:
                ships_survived.append(score)
                score = 0

            if row[0] == "":
                score = score + int(row[1])
                lock = 1
            else:
                score = score + int(row[1])
                lock = 0

            line_count = line_count + 1
        ships_survived.append(score)

def calculate_mines_cleared():
    file = open(midca_filename, "r")
    for line in file:
        if "Time Taken :" in line:
            score = line.replace("Time Taken :" , "")
            deadline.append(float(score))
        if "AGENT SCORE" in line:
            score = line.replace("AGENT SCORE : " , "")
            score_received.append(int(score))
    file.close()

def write_to_file():
    file = open(results_filename, "a+")
    for i in range(0, len(deadline)):
        file.write(str(ships_survived[i]) + ","  + str(score_received[i]) + "," + str(deadline[i]) + "\n")
    file.close()

calculate_scores()
calculate_mines_cleared()
write_to_file()
