# Tarea3_OrganizadorTareas
Tarea N°3 de Estructura de Datos, Ingeniería Civil Informática

Organizador de tareas implementado con las TDA árbol binario y lista.
======

---
**Antes de Empezar**

*   Usamos la aplicación `GitHub Desktop` para crear y actulizar nuestro repositorio local, ya que la misma aplicación realiza `git fetch` y `git pull`
*   Creamos un repositorio en GitHub, el link es el siguiente: 
*   Utilizamos Visual Studio Code para que ambos clonaramos el repositorio en sus computadores.
*   Para subir cada commit los comandos en git bash, como: `git status`, `git add .`, `git commit -m""` y `git push`
*   Para ejecutar el codigo se creo un script `compiler.sh` y así crear un archivo `.exe`.

---
En esta aplicacion implementamos las siguientes TDAs: 
* TDA Arbol binario:
  ````c
      typedef struct TreeNode TreeNode;

      struct TreeNode {
          Pair* pair;
          TreeNode * left;
          TreeNode * right;
          TreeNode * parent;
      };

      struct TreeMap {
          TreeNode * root;
          TreeNode * current;
          int (*lower_than) (void* key1, void* key2);
      };

      TreeNode * createTreeNode(void* key, void * value) {
      TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
      if (new == NULL) return NULL;
      new->pair = (Pair *)malloc(sizeof(Pair));
      new->pair->key = key;
      new->pair->value = value;
      new->parent = new->left = new->right = NULL;
      return new;
      }
  ````

* TDA Lista:

  ````c
  //Insertar
  
  ````
---
Se nos pidio crear una aplicación, la cual tiene por objetivo organizar las tareas por hacer. En donde el usuario ingresa el nombre de la tarea, la prioridad que tiene y establecer si tiene precedencia entre las otras tareas.

Para mantener ordenada nuestro proyecto utilizamos subcarpetas.

Para esto definimos la siguiente struct en c:

* Tarea

  ````c
  typedef struct {
    char nombreTarea[MAXCHAR];
    int prioridad;
    char tareaPrecedente[MAXCHAR];
    } Tarea;
  ````

