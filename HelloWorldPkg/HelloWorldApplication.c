#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
  UINTN Index = 0;
  EFI_STATUS Status = EFI_SUCCESS;

  if (SystemTable == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  if ((SystemTable->ConOut == NULL) || (SystemTable->ConOut->OutputString == NULL) || (SystemTable->ConOut->ClearScreen == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  if ((SystemTable->BootServices == NULL) || (SystemTable->BootServices->Stall == NULL))
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\nHello World!\r\n");
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  // Or we can use just Print function
  Print(L"Press any key to boot...!\n");
  Status = gBS->WaitForEvent(1, &(gST->ConIn->WaitForKey), &Index);

  if (EFI_ERROR(Status))
  {
    return Status;
  }

  gST->ConIn->Reset(gST->ConIn, FALSE);

  return EFI_SUCCESS;
}