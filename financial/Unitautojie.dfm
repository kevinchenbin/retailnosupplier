object frmautojieshuan: Tfrmautojieshuan
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #33258#21160#32467#31639
  ClientHeight = 160
  ClientWidth = 260
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 17
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 260
    Height = 160
    Align = alClient
    BevelInner = bvLowered
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitWidth = 264
    ExplicitHeight = 156
    object Label1: TLabel
      Left = 32
      Top = 23
      Width = 32
      Height = 22
      Caption = #24212#20184
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 32
      Top = 66
      Width = 32
      Height = 22
      Caption = #23454#32467
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 5
      Top = 99
      Width = 249
      Height = 17
      Caption = #65288#20313#39069#32467#27454#26102#23454#32467#20026#65306#20313#39069'+'#23454#38469#20184#65288#25910#65289#27454#65289
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object edityinhu: TEdit
      Left = 74
      Top = 22
      Width = 151
      Height = 25
      Alignment = taRightJustify
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object editshijie: TEdit
      Left = 72
      Top = 64
      Width = 153
      Height = 25
      Alignment = taRightJustify
      BiDiMode = bdLeftToRight
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      Text = '0.00'
      OnKeyPress = editshijieKeyPress
    end
    object RzButton1: TRzButton
      Left = 151
      Top = 124
      Width = 74
      Caption = #21462#28040
      Color = 16180174
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 74
      Top = 124
      Width = 71
      Caption = #30830#23450
      Color = 16180174
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = RzButton2Click
    end
  end
end