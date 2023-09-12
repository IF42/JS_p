/*
** základem jsou:
** lambda funkce 
** proměnné 
** seznamy
** slovníky
** n-tice
** high-order funkce
*/
import io as io

/*
** základní datové typy:
**
** str
** char
** int8
** int16
** int32
** int64
** uint8
** uint16
** uint32
** uint64
** integer
** float
** double
** real
** list - všechny položky musejí být stejného datového typu
** array - všechny položky musejí být stejného datového tyu
** tuple - může obsahovat různé datové typy, staticky typované musí být znamé v době překladu
** named-tuple - může obsahovat různé datové typy, staticky typované, musí být známé v době překladu
** dict  - může obsahovat různé datové typy, dynamicky typované, za běhu se může dynamicky měnit obsah, jeho položky musejí být typově indexované, méně efektvyní více dynamické
** lambda
** ptr
*/



/*
**
*/


enum Bool
{
    false
    , true
}


//konkrétní datové typyp si vynutím pomocí explicitního přetypování
// pomocí operátorů str() int32() uint32() char(), ...

const Persone = (name, age) => 
    {name: str(name), age: int32(age)}


const variable = "str value"


/**
** @brief
*/
const factorial = (n) => 
    n > 1 ? n * factorial(n - 1) : 1


const greed = (persone) => 
{
    print(`Hello, my name is ${this.name}`)
    return persone
}


const celebrate_birthday = (persone) =>
{
    persone.age ++;
    print(`Happy birthday! I am now ${persone.age} years old.`)

    return persone
}

/*
ukazatel je vlastně jen číslo, když napíšu kód
void * ptr = malloc(1);

tak mám v podstatě unsigned int proměnnou, která obsahuje paměťovou adresu.
Tato adresa je rozhraní do paměti, to znamená, že pointer v jako takový je pouze označení
že se s ním v programu pracuje ne jako s číslem ale jako s adresou. 
V JS+ ale nejsou pointery definované, takže to pro mě je jen číslo uint32/uint64

takže můžu udělat následující 

const object = uint64(gtk_window_new())

z pohledu filozofie jazyka mě tedy nezajímá jestli c funkce vrací ukazatel a nebo číslo
C funkce, která vrací ukazatel tedy vrací 32/64 bitové číslo


následující kódy by mělý být ekvivalentní


typedef struct List
{
    int data;
    List * next;
}List;


const List = (data, next) => {data: data, next: next}


l1 = List(42, List(27, None))

ale problém je když C funkce vrací ukazatel prostřednictvím parametrů...

const ND_Array = (data, shape) => {data: data, shape:shape}
const ND_Array = (data) => {data: data, data: [len(data)]}


*/
//jazyk python ctypes -> ffi


import ffi as ffi


const size = () =>
{
	a = int32()
	widget_size(ffi.byref(a))

    if(a > 0)
        return a
    else 
        return 0
}


const main = (args) =>
{
    persone = Persone("you", 22)
    person.greet().celebrateBirthday().greet()

    io.print([x*2 for x in range(1, 10)])
  
    return 0
}





