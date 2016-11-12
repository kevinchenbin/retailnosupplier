object frmMasterset: TfrmMasterset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #24635#24215#35774#32622
  ClientHeight = 165
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object pan1: TPanel
    Left = 0
    Top = 0
    Width = 310
    Height = 165
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object label1: TLabel
      Left = 24
      Top = 23
      Width = 36
      Height = 17
      Caption = #29616#24635#24215
    end
    object Label2: TLabel
      Left = 22
      Top = 65
      Width = 48
      Height = 17
      Caption = #39044#35774#24635#24215
    end
    object btok: TRzButton
      Left = 117
      Top = 115
      Caption = #30830#23450
      TabOrder = 0
      OnClick = btokClick
    end
    object btconcel: TRzButton
      Left = 198
      Top = 115
      Caption = #21462#28040
      TabOrder = 1
      OnClick = btconcelClick
    end
    object edname: TEdit
      Left = 76
      Top = 21
      Width = 197
      Height = 25
      AutoSize = False
      Ctl3D = False
      Enabled = False
      ParentCtl3D = False
      TabOrder = 2
    end
    object cbname: TComboBox
      Left = 76
      Top = 62
      Width = 197
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 0
      ParentCtl3D = False
      TabOrder = 3
    end
  end
  object cn: TADOConnection
    Left = 288
    Top = 128
  end
  object ds: TDataSource
    DataSet = aq
    Left = 288
    Top = 224
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 272
    Top = 296
  end
  object query: TADOQuery
    Parameters = <>
    Left = 280
    Top = 64
  end
end
