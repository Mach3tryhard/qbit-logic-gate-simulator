#include "manager.h"

int manager::Run() {
    Initialize();
    while(windowinst.isOpen()) {
        bool shouldExit = false;
        sf::Time dt = deltaClock.restart();

        Event_Loop(shouldExit);

        if(shouldExit || !windowinst.isOpen()) {
            if (windowinst.isOpen()) windowinst.close();
            break;
        }
        ///DOING GUI HERE APPARENTLY
        gui::getInstance().RunGui(windowinst,dt,nodes);

        instruments.HandleNodeContextMenu(windowinst, nodes);

        windowinst.clear();

        if (!ImGui::GetIO().WantCaptureMouse) {
            instruments.MultipleSelect(windowinst,nodes);
            instruments.DragSelected(windowinst, nodes);
            if (!instruments.get_multiple_select()) {
                instruments.UpdateConnectionDrag(windowinst, nodes);
            }
        }
        instruments.Deselect(nodes);

        /// MAIN DRAWING PLACE
        for (int i=0;i<nodes.size();i++) {
            nodes[i]->DisplayLines(windowinst);
        }
        for (int i=0;i<nodes.size();i++) {
            if (!nodes[i]->get_selected())
                nodes[i]->DisplayNode(windowinst);
        }
        for (int i=0;i<nodes.size();i++) {
            if (nodes[i]->get_selected())
                nodes[i]->DisplayNode(windowinst);
        }

        if (gui::getInstance().getMode() == 3) {
            instruments.DrawGhostNode(windowinst);
        }

        ImGui::SFML::Render(windowinst);
        windowinst.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

void manager::Event_Loop(bool& shouldExit) {
    while(const std::optional event = windowinst.pollEvent()) {
        ImGui::SFML::ProcessEvent(windowinst, *event);

        if (event->is<sf::Event::Closed>()) {
            shouldExit=true;
            windowinst.close();
        }

        if (event->is<sf::Event::KeyPressed>()) {
            const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                shouldExit = true;
            }
        }

        if (!ImGui::GetIO().WantCaptureMouse) {
            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (gui::getInstance().getMode()==0 || gui::getInstance().getMode()==1)
                    if (mousePress->button == sf::Mouse::Button::Left) instruments.CheckSelect(windowinst, nodes);
                if (gui::getInstance().getMode()==2)
                    if (mousePress->button == sf::Mouse::Button::Left) instruments.StartConnection(windowinst, nodes);
            }
            if (const auto* mouseRelease = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (gui::getInstance().getMode()==2)
                    if (mouseRelease->button == sf::Mouse::Button::Left)
                        instruments.EndConnection(windowinst, nodes);
                instruments.set_multiple_select(false);
            }
        }
    }
}