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

# PLANIFICACIÓN POR DEFECTO
if [[ $1 -eq 1 ]]; then
    echo PLANIFICACIÓN CON CHUNKS POR DEFECTO TAMAÑO 11520
    echo STATIC
    export OMP_SCHEDULE="monotonic:static"
    srun ./pmtv-OpenMP 11520
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic"
    srun ./pmtv-OpenMP 11520
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided"
    srun ./pmtv-OpenMP 11520

    echo PLANIFICACIÓN CON CHUNKS POR DEFECTO TAMAÑO 23040
    echo STATIC
    export OMP_SCHEDULE="monotonic:static"
    srun ./pmtv-OpenMP 23040
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic"
    srun ./pmtv-OpenMP 23040
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided"
    srun ./pmtv-OpenMP 23040
fi

# PLANIFICACIÓN CON CHUNK DE TAMAÑO 1
if [[ $1 -eq 2 ]]; then
    echo PLANIFICACIÓN CON CHUNKS 1 TAMAÑO 11520
    echo STATIC
    export OMP_SCHEDULE="monotonic:static,1"
    srun ./pmtv-OpenMP 11520
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic,1"
    srun ./pmtv-OpenMP 11520
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided,1"
    srun ./pmtv-OpenMP 11520

    echo PLANIFICACIÓN CON CHUNKS 1 TAMAÑO 23040
    echo STATIC
    export OMP_SCHEDULE="monotonic:static,1"
    srun ./pmtv-OpenMP 23040
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic,1"
    srun ./pmtv-OpenMP 23040
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided,1"
    srun ./pmtv-OpenMP 23040
fi

# PLANIFICACIÓN DE CHUNK DE TAMAÑO 64
if [[ $1 -eq 3 ]]; then
    echo PLANIFICACIÓN CON CHUNKS 64 TAMAÑO 11520
    echo STATIC
    export OMP_SCHEDULE="monotonic:static,64"
    srun ./pmtv-OpenMP 11520
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic,64"
    srun ./pmtv-OpenMP 11520
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided,64"
    srun ./pmtv-OpenMP 11520

    echo PLANIFICACIÓN CON CHUNKS 64 TAMAÑO 23040
    echo STATIC
    export OMP_SCHEDULE="monotonic:static,64"
    srun ./pmtv-OpenMP 23040
    echo DYNAMIC
    export OMP_SCHEDULE="monotonic:dynamic,64"
    srun ./pmtv-OpenMP 23040
    echo GUIDED
    export OMP_SCHEDULE="monotonic:guided,64"
    srun ./pmtv-OpenMP 23040
fi
