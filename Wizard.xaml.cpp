#include "pch.h"

#include "Wizard.xaml.h"

#include "MainPage.xaml.h"

using namespace RingClientUWP::Views;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Media::Capture;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Shapes;

Wizard::Wizard()
{
    InitializeComponent();
}

void
Wizard::_createAccountYes__Click(Object^ sender, RoutedEventArgs^ e)
{
    auto alias = _aliasTextBox_->Text;
    RingD::instance->_startingStatus = StartingStatus::REGISTERING_ON_THIS_PC;

    this->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([this] () {
        this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(RingClientUWP::MainPage::typeid));
        RingD::instance->createRINGAccount(_aliasTextBox_->Text, _password_->Password, true);
        _password_->Password = "";
    }));
}

void
Wizard::_showCreateAccountMenuBtn__Click(Object^ sender, RoutedEventArgs^ e)
{
    _accountAddMenuGrid_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    _showAddAccountMenuTitle_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    _showAddAccountMenuBtn_->Visibility = Windows::UI::Xaml::Visibility::Visible;

    _accountCreationMenuGrid_->Visibility = Windows::UI::Xaml::Visibility::Visible;
    _showCreateAccountMenuTitle_->Visibility = Windows::UI::Xaml::Visibility::Visible;
    _showCreateAccountMenuBtn_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}

void
Wizard::_showAddAccountMenuBtn__Click(Object^ sender, RoutedEventArgs^ e)
{
    _accountCreationMenuGrid_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    _showCreateAccountMenuTitle_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    _showCreateAccountMenuBtn_->Visibility = Windows::UI::Xaml::Visibility::Visible;

    _accountAddMenuGrid_->Visibility = Windows::UI::Xaml::Visibility::Visible;
    _showAddAccountMenuTitle_->Visibility = Windows::UI::Xaml::Visibility::Visible;
    _showAddAccountMenuBtn_->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}

void
Wizard::_avatarWebcamCaptureBtn__Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    CameraCaptureUI^ cameraCaptureUI = ref new CameraCaptureUI();
    cameraCaptureUI->PhotoSettings->Format = CameraCaptureUIPhotoFormat::Png;
    cameraCaptureUI->PhotoSettings->CroppedSizeInPixels = Size(100, 100);

    create_task(cameraCaptureUI->CaptureFileAsync(CameraCaptureUIMode::Photo))
    .then([this](StorageFile^ photoFile)
    {
        if (photoFile != nullptr) {
            // maybe it would be possible to move some logics to the style sheet
            auto brush = ref new ImageBrush();

            auto circle = ref new Ellipse();
            circle->Height = 80; // TODO : use some global constant when ready
            circle->Width = 80;
            auto path = photoFile->Path;
            auto uri = ref new Windows::Foundation::Uri(path);
            auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
            bitmapImage->UriSource = uri;

            StorageFolder^ localfolder = ApplicationData::Current->LocalFolder;
            String^ profilefolder = ".profile";
            create_task(localfolder->CreateFolderAsync(profilefolder,
                        Windows::Storage::CreationCollisionOption::OpenIfExists))
            .then([=](StorageFolder^ copytofolder) {
                try {
                    create_task(photoFile->CopyAsync(copytofolder))
                    .then([=](StorageFile^ copiedfile) {
                        copiedfile->RenameAsync("profile_image.png",
                                                Windows::Storage::NameCollisionOption::ReplaceExisting);
                    });
                }
                catch (Exception^ e) {
                    RingDebug::instance->print("Exception while saving profile image");
                }
            });

            Configuration::UserPreferences::instance->PREF_PROFILE_PHOTO = true;

            brush->ImageSource = bitmapImage;
            circle->Fill = brush;
            _avatarWebcamCaptureBtn_->Content = circle;
        }
    });

}

void RingClientUWP::Views::Wizard::_addAccountYes__Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    RingD::instance->_startingStatus = StartingStatus::REGISTERING_THIS_DEVICE;

    this->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
        this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(RingClientUWP::MainPage::typeid));
        RingD::instance->registerThisDevice(_PINTextBox_->Text, _ArchivePassword_->Password);
        _ArchivePassword_->Password = "";
        _PINTextBox_->Text = "";
    }));
}


void RingClientUWP::Views::Wizard::validatePassword(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    _createAccountYes_->IsEnabled = (_password_->Password
                                     == _passwordCheck_->Password
                                     && _password_->Password->Length() > 0)
                                    ? true : false;
}
