inherited frmorderquery1: Tfrmorderquery1
  BorderIcons = [biSystemMenu]
  Caption = #25209#37327#25171#21360
  ClientHeight = 467
  ClientWidth = 730
  ExplicitWidth = 736
  ExplicitHeight = 495
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel [0]
    Left = 539
    Top = 440
    Width = 31
    Height = 13
    Caption = 'Label3'
  end
  inherited Panel1: TPanel
    Width = 730
    Height = 467
    ExplicitWidth = 730
    ExplicitHeight = 467
    object Label2: TLabel [1]
      Left = 323
      Top = 439
      Width = 39
      Height = 17
      Caption = #24635#25968#37327':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel [2]
      Left = 455
      Top = 439
      Width = 39
      Height = 17
      Caption = #31038#30452#21457':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel [3]
      Left = 578
      Top = 438
      Width = 39
      Height = 17
      Caption = #28100#36716#21457':'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    inherited DBGrid1: TDBGrid
      Width = 716
    end
    inherited Button1: TButton
      Top = 64
      Width = 73
      Height = 29
      Caption = #26597#35810'(&S)'
      ExplicitTop = 64
      ExplicitWidth = 73
      ExplicitHeight = 29
    end
    inherited Button2: TButton
      Left = 657
      Top = 64
      Width = 73
      Height = 29
      Caption = #36864#20986'(&Q)'
      ExplicitLeft = 657
      ExplicitTop = 64
      ExplicitWidth = 73
      ExplicitHeight = 29
    end
    inherited cbshenghe: TCheckBox
      Left = 578
      ExplicitLeft = 578
    end
    inherited cbfahuofashi: TComboBox
      Left = 578
      Top = 9
      Width = 111
      ExplicitLeft = 578
      ExplicitTop = 9
      ExplicitWidth = 111
    end
    inherited cbchao: TCheckBox
      TabOrder = 23
    end
    inherited cboperator: TComboBox
      TabOrder = 22
    end
    inherited editorderbk: TEdit
      TabOrder = 24
    end
    object Button3: TButton
      Left = 576
      Top = 63
      Width = 73
      Height = 29
      Caption = #25171#21360'(&P)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 18
      OnClick = Button3Click
    end
    object edittotal: TEdit
      Left = 369
      Top = 436
      Width = 75
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 19
    end
    object editshe: TEdit
      Left = 497
      Top = 435
      Width = 75
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 20
    end
  end
  object editzhi: TEdit [2]
    Left = 624
    Top = 436
    Width = 75
    Height = 25
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
end
