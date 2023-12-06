
#include <wx/wx.h>


#include "structures.h"

#define WIDTH 1000
#define HEIGHT 700



class main_frame : public wxFrame {

    private:
        unsigned short contacts_count;

        // Create a menu bar
        wxMenuBar* menu_bar;
        wxMenu* file_item;
        
        void create_top_menu() {
            this->menu_bar = new wxMenuBar();

            // first create the "File dropdown"
            this->file_item = new wxMenu();
            
            // For Adding new contacts
            file_item->Append(wxID_ANY, "&Add Contact\tCtrl-Shift-A", "Save a new Contact to your phone book");
            file_item->AppendSeparator();

            // For Updating contact information.
            file_item->Append(wxID_ANY, "&Load Contacts...\tCtrl-L", "Load all contacts");
            file_item->Append(wxID_ANY, "&Remove Contacts...\tCtrl-D", "Delete a contact");
            file_item->Append(wxID_ANY, "&Update Contact...\tCtrl-U", "Update a contact's information");
            menu_bar->Append(file_item, "&File");

            SetMenuBar(menu_bar);
        }

        void add_contact() {
            // Add contacts to the database.
        }

    public:

        main_frame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
            this->create_top_menu();

            // the look itself of the screen.
            wxPanel* contacts_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
            contacts_panel->SetBackgroundColour(wxColour(100, 100, 200));

            wxPanel* messages_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
            messages_panel->SetBackgroundColour(wxColour(100, 200, 100));

            wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
            sizer->Add(contacts_panel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 10);
            sizer->Add(messages_panel, 3, wxEXPAND | wxALL, 10);

            this->SetSizerAndFit(sizer);
        }
};



class msg_c_app :public wxApp {

    public:
        bool OnInit() {
            main_frame* messaging_frame = new main_frame("Messaging C");
            messaging_frame->SetClientSize(WIDTH, HEIGHT);
            messaging_frame->Center();
            messaging_frame->Show();
            return true;
        }
};