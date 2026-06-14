# ASR5K-Lite CCS Workspace

ASR5K-style 的公開簡化版 Code Composer Studio workspace，用於作品集展示與可重現的 C2000 範例。

這個 repo 和私有 ASR5K 正式韌體 repo 是刻意分離的。它適合公開展示 CCS project structure、SysConfig 使用方式，以及不含機密內容的 F2838x workspace 範例。

## 1. Repository 角色

- **用途：** public reduced ASR5K demonstration workspace。
- **狀態：** public showcase repository。
- **可見性：** public。
- **範圍：** 乾淨的 CCS workspace 結構、SysConfig examples、非機密 project organization。
- **正式產品狀態：** 不是 ASR5K 正式韌體 repository。
- **正式 source of truth：** private `ASR5K_V2_Function` repository。

## 2. 目前 repository layout

此 repo 維持為乾淨的 CCS workspace，包含四個 CCS projects：

```text
ASR5K-Lite/
  .gitignore
  README.md
  sysconfig_cm/
  sysconfig_cpu1/
  sysconfig_cpu2/
  sysconfig_multi/
```

application source tree 不放在 repository root。CPU-specific source 與 SysConfig files 應留在各自的 CCS project directory 內。

## 3. 必要 TI 元件

最低測試環境：

```text
C2000Ware        6.00.01.00
SysConfig        1.24.0 or newer
SysConfig tested 1.27.1
C2000 compiler   ti-cgt-c2000_22.6.1.LTS
Device           F2838x / F28388D, 176-pin package
```

C2000Ware 6.00.01.00 需要 SysConfig 1.24.0 或更新版本。如果 CCS 使用舊版 SysConfig，build 會在 C compilation 前失敗，常見訊息如下：

```text
C2000 SysConfig version 6.00.01.00 requires at least version 1.24.0 of SysConfig.
```

請在 CCS 確認產品 discovery：

```text
Window > Preferences > Code Composer Studio > Products
```

應能看到 C2000Ware 6.00.01.00 與 SysConfig 1.24.0 或更新版本。

## 4. Build verification

CPU1 與 CPU2 的 RAM configuration 可用 shell 檢查：

```powershell
cd .\sysconfig_cpu1\RAM
& 'C:\ti\ccs1281\ccs\utils\bin\gmake' -k -j 16 all -O

cd ..\..\sysconfig_cpu2\RAM
& 'C:\ti\ccs1281\ccs\utils\bin\gmake' -k -j 16 all -O
```

預期輸出：

```text
sysconfig_cpu1/RAM/empty_sysconfig_cpu1.out
sysconfig_cpu2/RAM/empty_sysconfig_cpu2.out
```

CPU1 與 CPU2 的 FLASH configuration 也應能在 CCS 中 build。

## 5. Project notes

device support 由 SysConfig 產生。下列 legacy local files 可能仍留在 project tree，但應從 CPU1 / CPU2 build 排除，避免 duplicate symbols：

```text
device/device.c
device/F2838x_CodeStartBranch.asm
```

此 project 不應依賴 suppress 或 filter compiler/linker problems。既有 `--diag_suppress=10063` 屬於 imported CCS project settings；目前修正方向應是 path/source ownership，不是隱藏 log。

## 6. 常見問題

### `Build-variable COM_TI_C2000WARE_SOFTWARE_PACKAGE_* cannot be resolved`

project 不應依賴 deprecated package variables。pull changes 後請 refresh 或 re-import CCS projects。

### `symbol "Device_init" redefined` 或 `symbol "code_start" redefined`

build 同時編進 SysConfig-generated device support 與 legacy local device support files。請確認 `device/device.c` 和 `device/F2838x_CodeStartBranch.asm` 已從 CPU1 / CPU2 build configuration 排除。

### `cannot find file ".../driverlib.lib"`

請確認 C2000Ware 6.00.01.00 安裝在 configured path。測試用標準路徑如下：

```text
C:/ti/c2000/C2000Ware_6_00_01_00
```

## 7. Working rules

1. 保持此 repo public-safe。
2. 不加入機密 ASR5K implementation code。
3. 不加入 customer / product-specific hardware data。
4. generated build output 不進 version control。
5. examples 必須可重現且有文件說明。
