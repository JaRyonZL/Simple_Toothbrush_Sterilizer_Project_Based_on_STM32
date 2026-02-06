# Simple Toothbrush Sterilizer Project (基于 STM32)

本仓库是一个基于 STM32 的牙刷消毒器（简单消毒器）固件工程示例，使用 STM32F1 系列 MCU 与 ST 官方 HAL 驱动。该 README 旨在为后续回顾、维护与他人学习提供清晰的工程结构、关键点说明、构建与调试步骤，以及扩展建议。

## 主要目标

- 演示如何使用 STM32 HAL 实现牙刷消毒器的控制逻辑（风扇、加热、传感器、紫外线灯、数码管等）。
- 提供清晰的目录与模块划分，便于复用与扩展。
- 给出构建、烧录与调试的实用指南，帮助其他开发者快速上手硬件。

## 实现的功能

以下是根据仓库源码（`Application/`、`Interface/`、`Core/` 等目录）可以确认或推断出的已实现功能，便于快速回顾项目能力：

- 电源与系统初始化：基于 STM32 HAL 的时钟与外设初始化（`system_stm32f1xx.c`、CubeMX 配置）。
- 串口调试：`Com_Debug`（`Comment/Com_Debug.c`）用于输出运行日志与诊断信息，便于开发与故障排查。
- 按键输入：按键扫描逻辑（`Int_Key`），用于启动/停止、模式切换与用户交互。
- 状态机与业务逻辑：`app_toothbrush` 实现了消毒流程控制与模式管理（工作定时、开始/停止、运行状态切换等）。
- 风扇控制：`Int_Fan` 提供风扇开/关及档位控制（基于 GPIO 或 PWM/定时器实现）。
- 加热控制：`Int_Heat` 提供加热片的开启/关闭与时间控制。
- 传感器接口：`Int_Sensor` 提供霍尔传感器读取抽象（例如盖子状态检测），用于决策功能启停。
- 指示灯与数码管显示：`Int_LED` 与 `Int_NixieTube` 负责 LED 与数码管/数码显示，提供照明与倒计时等信息。
- 定时器与 PWM：`tim.c`/`tim.h` 提供定时器回调、占空比（PWM）和周期性任务支持（用于定时任务、去抖、PWM 输出等）。
- 中断处理：`stm32f1xx_it.c` 包含 ISR，外设中断仅做轻量处理并将复杂逻辑交给主循环或回调函数。
- 模块化硬件抽象：各硬件功能以 `Interface/Int_*.c` 的形式封装，易于替换与移植。

以上功能的实现使该工程成为一个完整的嵌入式应用示例，覆盖从外设驱动、硬件抽象到业务逻辑的端到端实现。

## 硬件与依赖

- MCU: STM32F1 系列（工程包含 `startup_stm32f103xb.s` / `system_stm32f1xx.c`，目标为 STM32F103 系列）。
- 外设: GPIO、TIM、USART、（可能使用 ADC 或 I2C/其他，视具体电路而定）。
- SDK/库: 使用 STM32 HAL（目录 `Drivers/STM32F1xx_HAL_Driver`），工程包含 CubeMX 生成的配置文件 `toothbrush_sanitizer_hal.ioc`。
- 开发环境: Keil uVision（工程文件位于 `MDK-ARM/`），也可使用支持的其他工具链（需要自行适配）。

## 快速上手

1. 打开 Keil uVision，然后打开工程文件：

	 - `MDK-ARM/toothbrush_sanitizer_hal.uvprojx`

2. 构建（Rebuild All）。
3. 连接调试器（如 ST-Link），下载程序到目标板，开始调试/运行。
4. 调试串口：工程中包含 `Com_Debug` 模块（`Comment/Com_Debug.c`）与 `Core/usart.c`，可用于打印日志，便于观察运行状态。

> 提示：源码中存在 `toothbrush_sanitizer_hal.ioc`（CubeMX 配置），可在 CubeMX 打开并查看时钟与外设初始化的具体设置。

## 仓库目录说明（逐目录详细解释）

- `Application/`
	- `app_toothbrush.c` / `app_toothbrush.h`：顶层应用逻辑（消毒器状态机、流程控制、模式与定时等）。这是实现“业务逻辑”的核心文件。

- `Core/`
	- `Inc/`：放置核心头文件，例如 `gpio.h`, `main.h`, `tim.h`, `usart.h` 等。
	- `Src/`：放置 HAL 以及系统初始化、外设配置实现，例如 `main.c`, `gpio.c`, `tim.c`, `usart.c`, `system_stm32f1xx.c` 等。
	- `stm32f1xx_it.c`：中断处理函数（ISR），包含外设中断入口与软中断分发逻辑。

- `Drivers/`
	- 包含 CMSIS 与 STM32 HAL 驱动（`Drivers/CMSIS/` 与 `Drivers/STM32F1xx_HAL_Driver/`）。这些是 HAL 层与启动相关文件，通常无需修改（除非移植或升级 HAL）。

- `Interface/`
	- `Int_Fan.c/h`, `Int_Heat.c/h`, `Int_Key.c/h`, `Int_LED.c/h`, `Int_NixieTube.c/h`, `Int_Ray.c/h`, `Int_Sensor.c/h`：硬件抽象层模块，每个文件对应一个具体外设接口或功能（例如风扇控制、加热控制、按键扫描、LED/数码管显示、光/射线控制、传感器读取等）。
	- 这些模块将具体的 GPIO/TIM/ADC/USART 操作封装为更高层的接口，便于在 `Application` 中调用。

- `Comment/`
	- `Com_Debug.c/h`：串口调试相关代码，用于在开发/调试阶段输出日志与状态。

- `MDK-ARM/`
	- Keil 专用工程文件、启动文件与构建输出，包含 `startup_stm32f103xb.s` 与 project settings。

- `DebugConfig/`、`RTE/`、`toothbrush_sanitizer_hal/` 等目录
	- 与项目构建、调试配置、编译中间文件和目标文件相关（IDE 生成）。通常不纳入版本控制或可忽略。


## 关键文件与功能映射（快速索引）

- `main.c`（`Core/Src/main.c`）
	- 程序入口，系统与外设初始化，主循环或任务调度入口。建议先从这里阅读，了解系统的启动流程与整体架构。

- `gpio.c` / `gpio.h`
	- 引脚初始化与抽象（列出重要引脚的功能映射 - 若项目未在代码中注释，请在阅读时补充注释以便维护）。

- `tim.c` / `tim.h`
	- 定时器初始化、PWM 输出、定时器回调（定时任务、按键去抖或占空比控制等）。

- `usart.c` / `usart.h`
	- 串口配置与中断/回调（用于 `Com_Debug` 与外设通信）。

- `app_toothbrush.c` / `app_toothbrush.h`
	- 牙刷消毒器的业务逻辑（状态机、工作模式、定时与安全保护逻辑）。

- `Int_*.c/h`
	- 各硬件模块封装：通过这些模块可以快速添加或替换硬件实现（例如不同型号的数码管或风扇驱动）。


## 代码风格与约定

- 使用 HAL API（不要直接操作寄存器，除非有性能或特殊要求）。
- 外设初始化在 `Core/Src` 中进行，具体业务逻辑放在 `Application/`。硬件抽象在 `Interface/` 中。
- 中断服务函数只放轻量逻辑（尽快返回）；复杂处理放到主循环或定时回调中。


## 构建与烧录（步骤）

1. 在开发板断电的情况下连接调试器（如 ST-Link）。
2. 打开 Keil 工程 `MDK-ARM/toothbrush_sanitizer_hal.uvprojx`。
3. 选择正确的目标芯片/链接脚本，编译（Project -> Rebuild）。
4. 使用 Keil 的 Download 或 Debug（需选择所用接口 SWD），将程序写入 Flash。
5. 运行并观察 `Com_Debug` 串口输出或板载指示灯行为确认功能。

如果你想使用命令行工具（例如 STM32CubeProgrammer）进行烧写，请先生成 hex/bin 文件并使用厂商工具进行下载——具体命令取决于你安装的工具，建议使用 STM 官方工具并参考其文档。


## 调试建议

- 使用 `Com_Debug`（串口）打印关键步骤、状态与错误代码。检查 `Comment/Com_Debug.c` 的波特率与串口配置（`Core/usart.c`）。
- 在关键位置添加状态量与断言，便于定位运行时问题。
- 如有外设异常，优先检查时钟配置（`system_stm32f1xx.c` 与 CubeMX 配置）与对应的 GPIO 复用设置。


## 扩展与二次开发建议

- 添加单元测试：当前工程没有单元测试框架，建议在 PC 上对算法与状态机进行脱机单元测试（例如使用 Unity/CMock 或在主机上用 Python/pytest 做逻辑验证）。
- 封装更多硬件抽象接口：当需要支持不同型号的数码管/传感器/驱动模块时，只需要实现相同接口即可替换。
- 增加配置管理：将常量与参数（定时、温度阈值、风扇转速档位等）放到一处（例如 `config.h`），便于调试与 OTA 升级时修改。


## 常见问题与排查要点

- 烧录失败：检查调试器连接（SWD 接线）、供电，以及是否有占用的外设（例如 Boot0 引脚状态）。
- 串口无输出：检查波特率、串口引脚映射、以及 `HAL_UART_Transmit`/中断是否正确配置。
- 按键不响应：检查按键 IO 是否上/下拉正确，以及按键去抖逻辑是否实现。


---

