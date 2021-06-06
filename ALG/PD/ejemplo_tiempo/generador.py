import random

for i in range(494,1000):
    nombre_archivo = "ej" + str(i);
    fich = open(nombre_archivo, "w")
    fich.write(str(i) + " " + str(i+1) + "\n")
    for j in range(i*(i+1)):
        fich.write(str(random.randint(1, 100)) + " ")
