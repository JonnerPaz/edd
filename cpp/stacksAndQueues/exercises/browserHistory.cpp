// BrowserHistory: simula navegación adelante/atrás de un navegador
//
// Usa dos stacks:
//   - backStack:    historial hacia atrás (páginas visitadas antes de la actual)
//   - forwardStack: historial hacia adelante (páginas a las que hicimos "atrás")
//   - currentPage:  página donde estamos ahora
//
// Operaciones:
//   visit(url)  → mueve currentPage a backStack, asigna nueva url, limpia forwardStack
//   goBack()    → mueve currentPage a forwardStack, saca de backStack → currentPage
//   goForward() → mueve currentPage a backStack, saca de forwardStack → currentPage
//
// Es el mismo comportamiento que un navegador real (Chrome, Firefox, etc.).

#include <iostream>
#include <string>

#include "../Stacks/stack.hpp"

class BrowserHistory
{
   private:
    Stack<std::string> backStack;
    Stack<std::string> forwardStack;
    std::string currentPage;

   public:
    BrowserHistory(const std::string& homepage) : currentPage(homepage) {}

    void visit(const std::string& url)
    {
        backStack.push(currentPage);
        currentPage = url;
        // Al visitar una nueva página, se borra el historial hacia adelante
        while (forwardStack.getSize() > 0) {
            forwardStack.pop();
        }
        std::cout << "Visitando: " << currentPage << "\n";
    }

    std::string goBack()
    {
        if (backStack.getSize() == 0) {
            std::cout << "No hay páginas hacia atrás.\n";
            return currentPage;
        }
        forwardStack.push(currentPage);
        currentPage = backStack.pop().value();
        std::cout << "← Atrás: " << currentPage << "\n";
        return currentPage;
    }

    std::string goForward()
    {
        if (forwardStack.getSize() == 0) {
            std::cout << "No hay páginas hacia adelante.\n";
            return currentPage;
        }
        backStack.push(currentPage);
        currentPage = forwardStack.pop().value();
        std::cout << "→ Adelante: " << currentPage << "\n";
        return currentPage;
    }

    std::string getCurrentPage() const { return currentPage; }
};

// Demo: simula sesión de navegación
int main()
{
    BrowserHistory browser("google.com");

    browser.visit("github.com");
    browser.visit("stackoverflow.com");
    browser.visit("youtube.com");

    browser.goBack();  // → stackoverflow.com
    browser.goBack();  // → github.com

    browser.visit("reddit.com");  // visita nueva → se pierde youtube.com y stackoverflow.com

    browser.goBack();     // → github.com
    browser.goForward();  // → reddit.com

    std::cout << "\nPágina actual: " << browser.getCurrentPage() << "\n";

    return 0;
}
