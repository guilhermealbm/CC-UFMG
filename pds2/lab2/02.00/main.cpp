#include <iostream>


int main(){
    long value1=200000;
    long value2;
    
    //imprima o valor do objeto apontado por long_ptr
    
    long *long_ptr;
    long_ptr = &value1;
    std::cout << *long_ptr << " ";
    
    //Imprima o valor de value2
    
    value2 = *long_ptr;
    std::cout << value2 << " ";
    
    //Imprima o endereço de value1
    
    std::cout << &value1 << " ";
    
    //Imprima o endereço armazenado em long_ptr
    
    std::cout << long_ptr << " ";
    
    //Imprima a comparação entre o endereço de value1 com o endereço armazenado em long_ptr
    
    bool comp;
    if(&value1 == long_ptr){
        comp = 1;
    }else{
        comp = 0;
    }
    std::cout << comp << " ";
        
    //imprimir os elementos do array values usando notação de array subscrito.
    
    unsigned int values[5];
    const int size = 5;
    
    values[0] = 2;
    values[1] = 4;
    values[2] = 6;
    values[3] = 8;
    values[4] = 10;
    
    unsigned int *v_ptr;
    
    for(int i = 0; i < size; i++){
        std::cout << values[i] << " ";
    }
    
    //v_ptr = &values;
    v_ptr = &values[0];
    
    //imprimir os elementos do array values usando notação de array ponteiro/deslocamento.
    
    for(int i = 0; i < size; i++){
        std::cout << *(v_ptr+i) << " ";
    }
    
    //imprimir os elementos do array values usando notação de array ponteiro/deslocamento com o nome de array como o ponteiro.
    
    for(int i = 0; i < size; i++){
        std::cout << *(values+i) << " ";
    }
    
    //imprimir os elementos do array values utilizando subscritos no ponteiro para o array.
    
    for(int i = 0; i < size; i++){
        std::cout << v_ptr[i] << " ";
    }
    
    //imprimir o quinto elemento de values utilizando a notação de subscrito de array,
    
    std::cout << values[4] << " ";
    
    //a notação de ponteiro/deslocamento com o nome de array como o ponteiro, 
    
    std::cout << *(values + 4) << " ";
    
    //a notação de subscrito de ponteiro,
    
    std::cout << v_ptr[4] << " ";
    
    //a notação de ponteiro/deslocamento.
    
    std::cout << *(v_ptr+4) << " ";
    
    //imprimir a comparação entre o valor armazenado em (v_ptr-4) e values[0]
    
    std::cout << (v_ptr+3) << " ";
    std::cout << *(v_ptr+3) << " ";
    std::cout << (v_ptr-4) << " ";
    std::cout << (values[0]) << " ";
    
    
    return 0;
}