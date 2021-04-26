#!/bin/bash
#Órdenes para el Gestor de carga de un trabajo:
#1. Asigna al trabajo un nombre
#SBATCH --job-name=SumaLocal
#2. Asignar el trabajo a una partición (cola)
#SBATCH --partition=ac
#3. Asignar el trabajo a un account
#SBATCH --account=ac

#Obtener información de las variables del entorno del Gestor de carga de trabajo:
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trbajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo: $SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"
#Instrucciones del script para ejecutar código:

echo "SECUENCIAL"
echo "Tamaño: 7500"
srun ./secuencial 7500

echo "Tamaño: 50000"
srun ./secuencial 50000

echo "PARALELO"
echo "Tamaño: 7500"
for i in `seq 1 1 32`; do
echo " -- Numero de cores: $i -- "
EXPORT OMP_NUM_THREADS=$i
srun ./paralelo 7500
done

echo "Tamaño: 50000"
for i in `seq 1 1 32`; do
export OMP_NUM_THREADS=$i
echo " -- Numero de cores: $i -- "
srun ./paralelo 50000
done


