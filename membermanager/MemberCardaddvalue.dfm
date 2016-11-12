object frmaddvalue: Tfrmaddvalue
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #20250#21592#21345#20805#20540
  ClientHeight = 188
  ClientWidth = 393
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 393
    Height = 188
    Align = alClient
    BevelInner = bvLowered
    Ctl3D = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentBackground = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 25
      Top = 16
      Width = 36
      Height = 17
      Caption = #25345#21345#20154
    end
    object Label2: TLabel
      Left = 219
      Top = 16
      Width = 24
      Height = 17
      Caption = #21345#21495
    end
    object Label3: TLabel
      Left = 13
      Top = 107
      Width = 48
      Height = 17
      Caption = #20805#20540#37329#39069
    end
    object Label4: TLabel
      Left = 13
      Top = 61
      Width = 48
      Height = 17
      Caption = #21345#20869#20313#39069
    end
    object edtcardname: TEdit
      Left = 78
      Top = 13
      Width = 120
      Height = 23
      Ctl3D = False
      Enabled = False
      ParentCtl3D = False
      TabOrder = 0
      OnChange = edtcardnameChange
    end
    object edtcardnum: TEdit
      Left = 247
      Top = 13
      Width = 120
      Height = 23
      Ctl3D = False
      Enabled = False
      ParentCtl3D = False
      TabOrder = 1
      OnChange = edtcardnumChange
    end
    object edtvalue: TEdit
      Left = 77
      Top = 59
      Width = 290
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 2
      OnChange = edtvalueChange
    end
    object edtaddvalue: TEdit
      Left = 76
      Top = 105
      Width = 292
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnChange = edtaddvalueChange
      OnKeyDown = edtaddvalueKeyDown
    end
    object btComfirm: TButton
      Left = 212
      Top = 152
      Width = 75
      Height = 25
      Caption = #20445#23384
      TabOrder = 4
      OnClick = btComfirmClick
    end
    object btConsel: TButton
      Left = 293
      Top = 152
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 5
      OnClick = btConselClick
    end
  end
  object MemberCardQuery: TADOQuery
    Parameters = <>
    Left = 24
    Top = 136
  end
  object quMemberRecord: TADOQuery
    Parameters = <>
    Left = 80
    Top = 144
  end
  object fcon: TADOConnection
    Left = 184
    Top = 144
  end
end
