# STM32 单片机学习

> STM32F103C8T6 | Keil MDK | Standard Peripheral Library | 江协科技教程
>
> 从 51 到 ARM Cortex-M3，用标准外设库理解寄存器背后的硬件逻辑。

---

## 🎯 学习路线

```
GPIO 基础 ──→ 中断/EXTI ──→ 定时器 ──→ PWM ──→ ADC ──→ DMA
  🔨             ⬜            ⬜          ⬜        ⬜        ⬜

  USART ──→ I2C/SPI ──→ RTC/BKP ──→ 低功耗 ──→ 看门狗 ──→ FLASH
   ⬜          ⬜           ⬜           ⬜          ⬜          ⬜
```

---

## 🔧 开发环境

| 项目 | 工具/芯片 |
|------|----------|
| 芯片 | STM32F103C8T6 (Cortex-M3, 64KB Flash, 20KB SRAM) |
| IDE | Keil MDK-ARM V5 |
| 库 | STM32F10x Standard Peripheral Library V3.5 |
| 下载器 | ST-Link V2 (SWD) |
| 开发板 | 最小系统板 + 面包板外设 |

---

## 📂 项目列表

### GPIO 基础

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| LED 闪烁 | `GPIO_learn/LED闪烁/` | RCC 时钟使能、GPIO 推挽输出、Delay 延时 | 07.25 |
| LED 流水灯 | `GPIO_learn/LED流水灯/` | 多引脚 GPIO 控制、移位流水灯 | 07.25 |
| 蜂鸣器 | `GPIO_learn/蜂鸣器/` | GPIO 驱动有源蜂鸣器 | 07.25 |
| 独立按键控制 LED | `GPIO_learn/独立按键控制LED/` | 按键输入检测、消抖、LED 翻转 | 07.25 |
| 光敏传感器控制蜂鸣器 | `GPIO_learn/光敏传感器控制蜂鸣器/` | 光敏电阻输入读取、多外设协同控制 | 07.25 |

### 中断 / EXTI

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

### 定时器

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

### PWM

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

### ADC / DMA

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

### 串口通信 (USART)

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

### I2C / SPI

| 项目 | 目录 | 核心技术 | 日期 |
|------|------|----------|------|
| — | — | ⬜ 待学习 | — |

---

## 📁 目录结构说明

```
stm32-learning/
├── 1-1 接线图/              # 每节课硬件连接示意图
├── 1-2 keilkill批处理/       # 编译缓存清理脚本
├── 1-3 Delay函数模块/        # 微秒/毫秒/秒延时函数模板
├── GPIO_learn/              # GPIO 章节各工程
├── STM32工程模板/            # 空白工程模板（Library + Start + User 骨架）
│   ├── Library/             # STM32F10x 标准外设库
│   ├── Start/               # CMSIS 启动文件 + 系统初始化
│   └── User/                # main.c / 中断服务 / 配置头
├── README.md
└── .gitignore
```

每个工程目录内部结构：

```
工程名/
├── User/main.c              # 主程序
├── User/stm32f10x_conf.h    # 标准库模块裁剪
├── User/stm32f10x_it.c/h    # 中断服务函数
├── Hardware/                # 自写外设驱动（如 LED / Key / Buzzer）
├── System/Delay.c/h         # 系统延时
├── Library/                 # 标准外设库（共享拷贝）
├── Start/                   # CMSIS（共享拷贝）
├── Project.uvprojx          # Keil 工程文件
└── keilkill.bat             # 清理编译缓存
```

---

## 🆚 与 51 单片机的关键区别

| | 51 (STC89C52) | STM32 (F103C8T6) |
|---|---|---|
| 架构 | 8-bit 8051 | 32-bit ARM Cortex-M3 |
| 主频 | 11.0592 MHz / 12 MHz | 72 MHz |
| 时钟源 | 外部晶振，固定 | 多时钟源，PLL 倍频，每个外设独立时钟开关 |
| GPIO | `P1 = 0xFE;` 直接赋值 | 需使能时钟 + 配置模式/速度，用库函数操作 |
| 外设驱动 | 手写寄存器 | 标准外设库 (Standard Peripheral Library) |
| 烧录 | STC-ISP 串口冷启动 | ST-Link SWD 一键下载调试 |
| 调试 | 无 | 硬件断点、单步、变量监视 |

---

## 📝 学习笔记

- **GPIO 初始化四步**：开 RCC 时钟 → 配置 GPIO_InitStructure（Mode/Pin/Speed） → GPIO_Init() → 用 GPIO_WriteBit/ReadBit 操作
- **库函数命名规律**：`外设缩写_功能名()`，如 `GPIO_Init()`, `USART_SendData()`
- **所有外设必须先开 RCC 时钟**，这点 51 没有，也是新手最常见的坑
- **`stm32f10x_conf.h`** 是标准库的模块开关，只用某个外设就只打开对应头文件，否则编译慢
- **启动文件只保留 `startup_stm32f10x_md.s`**（md = medium density，对应 STM32F103C8）
