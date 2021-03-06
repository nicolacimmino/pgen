#include "UnlockEncryptedStoreService.h"

UnlockEncryptedStoreService::UnlockEncryptedStoreService(Terminal *terminal, EncryptedStore *encryptedStore, NotificationController *notificationController, const Functor1<byte> &reportProgress, const Functor0 &reportCompletion)
    : Service(reportProgress, reportCompletion)
{
    this->terminal = terminal;
    this->encryptedStore = encryptedStore;
    this->notificationController = notificationController;
}

bool UnlockEncryptedStoreService::start(byte arg = 0)
{
    this->notificationController->setIdle(true);
    
    while(true) {
        if(this->terminal->clientRequestedAbort()) {
            break;
        }

        this->terminal->flushInput();
        this->notificationController->loop();
    }

    this->notificationController->setIdle(false);
    
    this->terminal->clearScreen();

    char *masterPassword = new char[ENCRYPTED_STORE_MASTER_PASSWORD_MAX_SIZE];

    if (this->terminal->askQuestion(TXT_ENTER_MASTER_PASSWORD, masterPassword, ENCRYPTED_STORE_MASTER_PASSWORD_MAX_SIZE, TXT_PASSWORD_MASK, TERMINAL_FIRST_CANVAS_LINE + 2, 2, true) == true)
    {
        this->encryptedStore->unlock(masterPassword);

        this->notificationController->setStoreLocked(false, this->encryptedStore->getKeyFingerprint());
    }

    delete masterPassword;

    this->reportCompletion();

    return false;
}

bool UnlockEncryptedStoreService::loop()
{
    return this->running;
}