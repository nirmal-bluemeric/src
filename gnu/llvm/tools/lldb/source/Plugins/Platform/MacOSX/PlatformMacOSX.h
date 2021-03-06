//===-- PlatformMacOSX.h ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_PlatformMacOSX_h_
#define liblldb_PlatformMacOSX_h_

#include "PlatformDarwin.h"

class PlatformMacOSX : public PlatformDarwin {
public:
  PlatformMacOSX(bool is_host);

  ~PlatformMacOSX() override;

  //------------------------------------------------------------
  // Class functions
  //------------------------------------------------------------
  static lldb::PlatformSP CreateInstance(bool force,
                                         const lldb_private::ArchSpec *arch);

  static void Initialize();

  static void Terminate();

  static lldb_private::ConstString GetPluginNameStatic(bool is_host);

  static const char *GetDescriptionStatic(bool is_host);

  //------------------------------------------------------------
  // lldb_private::PluginInterface functions
  //------------------------------------------------------------
  lldb_private::ConstString GetPluginName() override {
    return GetPluginNameStatic(IsHost());
  }

  uint32_t GetPluginVersion() override { return 1; }

  lldb_private::Status
  GetSharedModule(const lldb_private::ModuleSpec &module_spec,
                  lldb_private::Process *process, lldb::ModuleSP &module_sp,
                  const lldb_private::FileSpecList *module_search_paths_ptr,
                  lldb::ModuleSP *old_module_sp_ptr,
                  bool *did_create_ptr) override;

  const char *GetDescription() override {
    return GetDescriptionStatic(IsHost());
  }

  lldb_private::Status
  GetSymbolFile(const lldb_private::FileSpec &platform_file,
                const lldb_private::UUID *uuid_ptr,
                lldb_private::FileSpec &local_file);

  lldb_private::Status
  GetFile(const lldb_private::FileSpec &source,
          const lldb_private::FileSpec &destination) override {
    return PlatformDarwin::GetFile(source, destination);
  }

  lldb_private::Status
  GetFileWithUUID(const lldb_private::FileSpec &platform_file,
                  const lldb_private::UUID *uuid_ptr,
                  lldb_private::FileSpec &local_file) override;

  bool GetSupportedArchitectureAtIndex(uint32_t idx,
                                       lldb_private::ArchSpec &arch) override;

  lldb_private::ConstString
  GetSDKDirectory(lldb_private::Target &target) override;

  void
  AddClangModuleCompilationOptions(lldb_private::Target *target,
                                   std::vector<std::string> &options) override {
    return PlatformDarwin::AddClangModuleCompilationOptionsForSDKType(
        target, options, PlatformDarwin::SDKType::MacOSX);
  }

private:
  DISALLOW_COPY_AND_ASSIGN(PlatformMacOSX);
};

#endif // liblldb_PlatformMacOSX_h_
