import numpy as np 
import matplotlib.pyplot as plt 

from matplotlib import cm

import sys


def create_fig(name_param, i):
	#create matrix
	displayed_param = [ [ 0 for _ in range(len(b_seeds))] for _ in range(len(t_seeds))]

	for game in games:
		displayed_param[int(game["seed_token"])][int(game["seed_builders"])] = game[name_param]

	#parse into numpy array
	displayed_param = np.array(displayed_param)

	#Create figure
	#fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
	fig = plt.figure(i)
	ax = fig.add_subplot(111, projection='3d')
	#ax = plt.axes(projection = "3d")

	ax.plot_surface(B, T, displayed_param, cmap=cm.coolwarm, linewidth=0,antialiased=False)
	#to be sure
	# b_seeds_2 = np.array([game["seed_builders"] for game in games])
	# t_seeds_2 = np.array([game["seed_token"] for game in games])
	# turns = np.array( [game["nb_turns"] for game in games])


	#Set labels
	ax.set_xlabel("Builder seed")
	ax.set_ylabel("Token seed")
	ax.set_zlabel(name_param)
	ax.set_title(name_param + " compared to the builder and token seed")

	#Set default view
	ax.view_init(elev=30, azim=-130, roll=0)
	return fig

output = open("output.out")
#Get params
params = [ param.strip("\n") for param in output.readline().split(";") ]
num_param = len(params)
choices_str = ["HIRE", "PICK", "SKIP"]

#parse game data 
games = []
for line in output :
	game = {}
	
	for i, data in enumerate(line.split(";")) :
		#specific action for the choices
		if params[i] == "choices":
			game[params[i]] = {}
			for j, choice in enumerate(data.split(",")):
				game[params[i]][choices_str[j]] = float(choice)
		else : 
			game[params[i]] = float(data.strip("\n"))
	games.append(game)
output.close()

#get builder and token seeds
b_seeds = np.array(list(set([game["seed_builders"] for game in games])))
t_seeds = np.array(list(set([game["seed_token"] for game in games]))) #use set to get unique seed

B , T = np.meshgrid(b_seeds, t_seeds)

##Choose wich param we wanted to display
argv = sys.argv

if len(argv) == 1:
	params[0] = "nb_turns"
	num_fig = 1
else :
	if argv[1] == "all":
		num_fig = num_param
	elif argv[1] not in params:
		print(argv[1] + " is not a game parameter\n")
		exit(1)
	else :	
		params[0] = argv[1]
		num_fig = 1

for i in range(num_fig):
	if params[i] == "choices":
		continue
	create_fig(params[i], i)

plt.show()

