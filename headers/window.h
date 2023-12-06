
#include <wx/wx.h>


#include "structures.h"

#define WIDTH 1000
#define HEIGHT 700
#define CONTACT_WIDTH (WIDTH / 5)
#define MSG_WIDTH (WIDTH - CONTACT_WIDTH)



class frame : public wxFrame {

    private:
        unsigned short contacts_count;

        void add_contact() {
            // Add contacts to the database.
        }

    public:

        frame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
            
            // The bar that appears at the top of the screen
            wxMenuBar* menu_bar = new wxMenuBar();

            wxMenu* file_item = new wxMenu();
            file_item->Append(wxID_ANY, "&Add Contact\tCtrl-Shift-T", "Save a new Contact to your phone book");

            menu_bar->Append(file_item, "&File");

            SetMenuBar(menu_bar);
            CreateStatusBar();
            SetStatusText("Welcome to Messaging C!");

            // the look itself of the screen.
            wxPanel* contacts_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
            contacts_panel->SetBackgroundColour(wxColor(100, 100, 200));

            wxPanel* messages_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
            messages_panel->SetBackgroundColour(wxColor(100, 200, 100));

            wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
            sizer->Add(contacts_panel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 10);
            sizer->Add(messages_panel, 3, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 10);

            this->SetSizerAndFit(sizer);
        }
};



class msg_c_app :public wxApp {

    public:
        bool OnInit() {
            frame* messaging_frame = new frame("Messaging C");
            messaging_frame->SetClientSize(WIDTH, HEIGHT);
            messaging_frame->Center();
            messaging_frame->Show();
            return true;
        }
};