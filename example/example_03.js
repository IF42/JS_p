

class Itegral
{
    operator (+) = (T, T) => T 
    operator (-) = (T, T) => T
}


const instance int
{
    operator (+) = (a:int, b:int) => 
}


const factorial = (int n) : int => 
{
    if(n > 1)
        return n * factorial(n-1);
    else
        return 1;
}


const window_get_default_size = (widget : GtkWidget*) => 
{
    width : int = 0;
    height: int = 0;

    gtk_window_get_default_size(widget, &width, &height);

    return (width, height);
}

struct Tensor 
{
    array, shape
}



// přetížení operátorů, existuje pevný počet operátorů, které je možné přetížit pro daný typ
// typové třídy
// všechny funkce jsou anonymní, ale lze je vložit do globálních proměnných
// primitivní datové typy vestavěné do jazyka/překladače 
// neexistuje void * ukazatel, pouze generický ukazatel, který je přetypován na konkrétní datový typ při překladu, kdy se zaručí že předávaný argument obsahuje to co má

main :: (args) =>
{
    t = T()
}
    



