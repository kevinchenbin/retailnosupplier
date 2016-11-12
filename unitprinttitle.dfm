object frmprinttitle: Tfrmprinttitle
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #25171#21360#20449#24687#35774#32622
  ClientHeight = 284
  ClientWidth = 558
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 558
    Height = 284
    Align = alClient
    BevelInner = bvLowered
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 2
      Top = 2
      Width = 554
      Height = 280
      ActivePage = taborder
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 0
      object taborder: TTabSheet
        Caption = #35746#21333
        object GroupBox2: TGroupBox
          Left = 6
          Top = 5
          Width = 537
          Height = 164
          Caption = #35746#21333#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label6: TLabel
            Left = 8
            Top = 30
            Width = 48
            Height = 17
            Caption = #21333#25454#25260#22836
          end
          object Label7: TLabel
            Left = 32
            Top = 93
            Width = 24
            Height = 17
            Caption = #22320#22336
          end
          object Label8: TLabel
            Left = 20
            Top = 62
            Width = 36
            Height = 17
            Caption = #32852#31995#20154
          end
          object Label9: TLabel
            Left = 306
            Top = 62
            Width = 24
            Height = 17
            Caption = #30005#35805
          end
          object Label4: TLabel
            Left = 8
            Top = 125
            Width = 72
            Height = 17
            Caption = #35746#21333#25171#21360#22791#27880
          end
          object edorprintbk: TEdit
            Left = 86
            Top = 122
            Width = 434
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 0
          end
          object edorprinttitle: TEdit
            Left = 62
            Top = 27
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 1
          end
          object edoraddress: TEdit
            Left = 62
            Top = 90
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 2
          end
          object edorcontact: TEdit
            Left = 62
            Top = 59
            Width = 91
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 3
          end
          object edortel: TEdit
            Left = 336
            Top = 59
            Width = 184
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 4
          end
        end
        object RzButton1: TRzButton
          Left = 468
          Top = 175
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton1Click
        end
      end
      object tabcaigou: TTabSheet
        Caption = #37319#36141
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox1: TGroupBox
          Left = 1
          Top = 5
          Width = 537
          Height = 214
          Caption = #37319#36141#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label1: TLabel
            Left = 18
            Top = 28
            Width = 48
            Height = 17
            Caption = #21333#25454#25260#22836
          end
          object Label2: TLabel
            Left = 42
            Top = 92
            Width = 24
            Height = 17
            Caption = #22320#22336
          end
          object Label3: TLabel
            Left = 30
            Top = 60
            Width = 36
            Height = 17
            Caption = #32852#31995#20154
          end
          object Label5: TLabel
            Left = 306
            Top = 60
            Width = 24
            Height = 17
            Caption = #30005#35805
          end
          object Label10: TLabel
            Left = 8
            Top = 186
            Width = 72
            Height = 17
            Caption = #37319#36141#25171#21360#22791#27880
          end
          object Label21: TLabel
            Left = 18
            Top = 155
            Width = 48
            Height = 17
            Caption = #25910#36135#22320#22336
          end
          object Label22: TLabel
            Left = 6
            Top = 123
            Width = 60
            Height = 17
            Caption = #25910#36135#32852#31995#20154
          end
          object Label23: TLabel
            Left = 282
            Top = 123
            Width = 48
            Height = 17
            Caption = #25910#36135#30005#35805
          end
          object edcgprintbk: TEdit
            Left = 86
            Top = 183
            Width = 434
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 0
          end
          object edcgprinttitle: TEdit
            Left = 69
            Top = 26
            Width = 451
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 1
          end
          object edcgaddress: TEdit
            Left = 69
            Top = 89
            Width = 451
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 2
          end
          object edcgcontact: TEdit
            Left = 69
            Top = 57
            Width = 84
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 3
          end
          object edcgtel: TEdit
            Left = 336
            Top = 57
            Width = 184
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 4
          end
          object edshaddress: TEdit
            Left = 69
            Top = 152
            Width = 451
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 5
          end
          object edshcontact: TEdit
            Left = 69
            Top = 120
            Width = 91
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 6
          end
          object edshtel: TEdit
            Left = 336
            Top = 120
            Width = 184
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 7
          end
        end
        object RzButton2: TRzButton
          Left = 468
          Top = 221
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton2Click
        end
      end
      object rabrk: TTabSheet
        Caption = #20837#24211
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox3: TGroupBox
          Left = 6
          Top = 5
          Width = 537
          Height = 170
          Caption = #20837#24211#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label11: TLabel
            Left = 8
            Top = 29
            Width = 48
            Height = 17
            Caption = #21333#25454#25260#22836
          end
          object Label12: TLabel
            Left = 32
            Top = 95
            Width = 24
            Height = 17
            Caption = #22320#22336
          end
          object Label13: TLabel
            Left = 20
            Top = 62
            Width = 36
            Height = 17
            Caption = #32852#31995#20154
          end
          object Label14: TLabel
            Left = 306
            Top = 62
            Width = 24
            Height = 17
            Caption = #30005#35805
          end
          object Label15: TLabel
            Left = 8
            Top = 128
            Width = 72
            Height = 17
            Caption = #20837#24211#25171#21360#22791#27880
          end
          object edrkprintbk: TEdit
            Left = 86
            Top = 125
            Width = 434
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 0
          end
          object edrkprinttitle: TEdit
            Left = 62
            Top = 27
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 1
          end
          object edrkaddress: TEdit
            Left = 62
            Top = 92
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 2
          end
          object edrkcontact: TEdit
            Left = 62
            Top = 59
            Width = 91
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 3
          end
          object edrktel: TEdit
            Left = 336
            Top = 59
            Width = 184
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 4
          end
        end
        object RzButton3: TRzButton
          Left = 468
          Top = 181
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton3Click
        end
      end
      object tabws: TTabSheet
        Caption = #21457#36135
        ImageIndex = 3
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox4: TGroupBox
          Left = 1
          Top = 6
          Width = 537
          Height = 163
          Caption = #21457#36135#20449#24687
          TabOrder = 0
          object Label16: TLabel
            Left = 8
            Top = 30
            Width = 48
            Height = 17
            Caption = #21333#25454#25260#22836
          end
          object Label17: TLabel
            Left = 32
            Top = 91
            Width = 24
            Height = 17
            Caption = #22320#22336
          end
          object Label18: TLabel
            Left = 20
            Top = 60
            Width = 36
            Height = 17
            Caption = #32852#31995#20154
          end
          object Label19: TLabel
            Left = 306
            Top = 60
            Width = 24
            Height = 17
            Caption = #30005#35805
          end
          object Label20: TLabel
            Left = 8
            Top = 122
            Width = 72
            Height = 17
            Caption = #21457#36135#25171#21360#22791#27880
          end
          object edwsprinttitle: TEdit
            Left = 62
            Top = 27
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 0
          end
          object edwsaddress: TEdit
            Left = 62
            Top = 88
            Width = 458
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 1
          end
          object edwscontact: TEdit
            Left = 62
            Top = 57
            Width = 91
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 2
          end
          object edwstel: TEdit
            Left = 336
            Top = 57
            Width = 184
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 3
          end
          object edpxprintbk: TEdit
            Left = 86
            Top = 119
            Width = 434
            Height = 23
            Ctl3D = False
            ParentCtl3D = False
            TabOrder = 4
          end
        end
        object RzButton4: TRzButton
          Left = 463
          Top = 175
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton4Click
        end
      end
    end
  end
  object fcon: TADOConnection
    Left = 352
    Top = 8
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 480
  end
end
