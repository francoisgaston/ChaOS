#include <libc.h>
#include <test_util.h>
//TODO: sacar
#include "../include/libc.h"
#include "../include/test_util.h"
//---------------------------------------------------------------------------------
// help: imprime informacion sobre los programas disponibles
//---------------------------------------------------------------------------------
// Argumentos:
//  arg_c: cantidad de argumentos del programa (0)
//  arg_v: arreglo con los strings de los argumentos
//---------------------------------------------------------------------------------
void help(uint64_t arg_c, const char ** arg_v){
    extern front_program_t programs[CANT_PROG];
    if(arg_c!=0){
        throw_error("Error: el programa no recibe argumentos");
    }
    print_string("Programas disponibles:\n");
    for(int i = 0; i<CANT_PROG;i++){
        print_string(programs[i].desc);
    }
    sys_exit();
}

void mem(uint64_t arg_c, const char ** arg_v){
    mm_info_t aux;
    sys_mm_info(&aux);
    print_string_with_padding("Total bytes:",40);
    print_number(aux.total_bytes);
    print_string("\n");
    print_string_with_padding("Allocated bytes:",40);
    print_number(aux.allocated_bytes);
    print_string("\n");print_string_with_padding("Allocated blocks:",40);
    print_number(aux.allocated_blocks);
    print_string("\n");print_string_with_padding("Free bytes:",40);
    print_number(aux.free_bytes);
    print_string("\n");
}

void ps(uint64_t arg_c, const char ** arg_v){
    char* status[] = {"Execute","Ready","Blocked","Finished"};
    uint64_t processes = sys_get_process_count();//OJO si son muchos!!!!
    process_info_t* aux = sys_mm_alloc(processes*sizeof (process_info_t));
    processes = sys_get_scheduler_info(aux,processes);
    print_string_with_padding("PID",8);
    print_string_with_padding("Name",20);
    print_string_with_padding("Status",10);
    print_string_with_padding("Priority",8);
    print_string_with_padding("BP",10);
    print_string_with_padding("SP",10);
    print_string_with_padding("Foreground",12);
    print_string("\n");
    char buf[20];
    for(int i = 0; i<processes; i++){
        number_to_string(aux[i].pid,buf);
        print_string_with_padding(buf,8);
        print_string_with_padding(aux[i].name,20);
        print_string_with_padding(status[aux[i].status],10);
        number_to_string(aux[i].priority,buf);
        print_string_with_padding(buf,8);
        print_string_with_padding(to_hex(buf,aux[i].bp),10);
        print_string_with_padding(to_hex(buf,aux[i].sp),10);
        print_string_with_padding(aux[i].foreground?"True":"False",12);
        print_string("\n");
    }
    sys_mm_free(aux);
}
void loop(uint64_t arg_c, const char ** arg_v){
    while(1){
        print_number(getpid());
        pause_ticks(10);
    }
}
void kill(uint64_t arg_c, const char ** arg_v){
    if(arg_c!=1){
        throw_error("Error: el programa debe recibir el pid del proceso que se desea matar");
        return;
    }
    uint64_t pid;
    if((pid = satoi(arg_v[0])) <= 0){
        throw_error("Error: el argumento ingresado para el pid no es valido");
        return;
    }
    terminate_process(pid);
}
void nice_command(uint64_t arg_c, const char ** arg_v){
    if(arg_c!=2){
        throw_error("Error: el programa debe recibir el pid del proceso cuya prioridad se desea cambiar y su nueva prioridad entre 0 y 4");
        return;
    }
    uint64_t pid;
    uint8_t prio;
    if((pid = satoi(arg_v[0])) <= 0){
        throw_error("Error: el argumento ingresado para el pid no es valido");
        return;
    }
    if((prio = satoi(arg_v[1])) < 0 || prio>=5 || prio<0){
        throw_error("Error: el argumento ingresado para la prioridad no es valido");
        return;
    }
    if(sys_nice(pid,prio)==-1){
        print_string("Ocurrio un error al intentar cambiar la prioridad del proceso.\n Asegurese de que el proceso no haya terminado\n");
    }
}
void block(uint64_t arg_c, const char ** arg_v){
    if(arg_c!=1){
        throw_error("Error: el programa debe recibir el pid del proceso que se desea bloquear");
        return;
    }
    uint64_t pid;
    if((pid = satoi(arg_v[0])) <= 0){
        throw_error("Error: el argumento ingresado para el pid no es valido");
        return;
    }
    if(block_process(pid)==-1){
        print_string("Ocurrio un error al intentar bloquear el proceso.\n Asegurese de que el proceso no este bloqueado o terminado\n");
    }
}
void unblock(uint64_t arg_c, const char ** arg_v){
    if(arg_c!=1){
        throw_error("Error: el programa debe recibir el pid del proceso que se desea desbloquear");
        return;
    }
    uint64_t pid;
    if((pid = satoi(arg_v[0])) <= 0){
        throw_error("Error: el argumento ingresado para el pid no es valido");
        return;
    }
    if(unblock_process(pid)==-1){
        print_string("Ocurrio un error al intentar desbloquear el proceso.\n Asegurese de que el proceso este bloqueado\n");
    }
}
void wait_pid_command(uint64_t arg_c, const char ** arg_v){
    if(arg_c!=1){
        throw_error("Error: el programa debe recibir el pid del proceso que se desea esperar");
        return;
    }
    uint64_t pid;
    if((pid = satoi(arg_v[0])) <= 0){
        throw_error("Error: el argumento ingresado para el pid no es valido");
        return;
    }
    waitpid(pid);
}

void sem(uint64_t arg_c, const char ** arg_v){
    sem_dump_t* aux_sem_dump;
    int32_t count = sys_sem_count();
    aux_sem_dump = sys_mm_alloc(count*sizeof (sem_dump_t));
    count = sem_info(aux_sem_dump,count);
    for(int i = 0; i<count; i++){
        if(aux_sem_dump[i].name!=NULL){
        print_string("Semaforo: ");
        print_string(aux_sem_dump[i].name!=NULL?aux_sem_dump[i].name:"sin nombre");
        print_string(", Valor: ");
        print_number(aux_sem_dump[i].value);
        print_string("\n");
        print_string("Procesos bloqueados: ");
        print_numbers(aux_sem_dump[i].blocked_processes,aux_sem_dump[i].blocked_size);
        print_string("\n");
        print_string("Procesos conectados: ");
        print_numbers(aux_sem_dump[i].connected_processes,aux_sem_dump[i].connected_size);
        print_string("\n");
        }
    }
    free_sem_info(aux_sem_dump,count);
    free(aux_sem_dump);
}
void pipe_info(uint64_t arg_c, const char ** arg_v){
    //TODO
}