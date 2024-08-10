#include <iostream>
#include <vector>
using namespace std;

struct Archivo {
    string name;
};

/* Recursividad  */
struct Directorio {
    string name;
    vector <Archivo> archivos;
    vector <Directorio> subdirectorio;
};

bool findFile(Directorio& dir, string& path, string& target) {

    for(auto arch: dir.archivos) {
        if(arch.name == target) {
            path += "/" + dir.name; /* Esta pegando sucesivamente los paths pasados a la direccion actual*/
            return true;
        }
    }

    for(auto& subdir: dir.subdirectorio) {
        string subdirpath = path + "/" + dir.name;
        if(findFile(subdir, subdirpath, target)) {
            path = subdirpath;
            return true;
        }
    }
    return false;
}

int main()
{
    Directorio sistemaDeArchivos = {
        "root",
        {
               {"archivo1.txt"},
               {"archivo2.txt"}
        },
        {
               {
                   "subdir1",
                   {
                       {"archivo3.txt"},
                   },
                   {
                       {
                           "subdir2",
                           {
                               {"target.txt"},
                               {"archivo4.txt"}
                           },
                           {}
                       }
                   }
               },
               {"archivo5.txt"}
        }
    };

    string target = "archivo3.txt";
    string path = "";

    if(findFile(sistemaDeArchivos, path, target)) {
        cout <<"Archivo encontrado en: " << path << "/" << target;
    } else {
        cout << "Archivo no encontrado :(" << endl;
    }

    return 0;
}
