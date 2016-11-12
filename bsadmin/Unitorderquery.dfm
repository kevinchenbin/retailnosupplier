object frmorderquery: Tfrmorderquery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #26597#21333
  ClientHeight = 448
  ClientWidth = 753
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
    Width = 753
    Height = 448
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 156
      Top = 71
      Width = 12
      Height = 17
      Caption = #21040
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object dtpstart: TDateTimePicker
      Left = 85
      Top = 7
      Width = 156
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 5
      Top = 11
      Width = 74
      Height = 17
      Caption = #36215#22987#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object dtpend: TDateTimePicker
      Left = 325
      Top = 7
      Width = 156
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 247
      Top = 11
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object chclient: TCheckBox
      Left = 5
      Top = 41
      Width = 65
      Height = 17
      Caption = #23458#25143
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object edclient: TEdit
      Left = 85
      Top = 37
      Width = 72
      Height = 25
      AutoSize = False
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 5
      OnKeyPress = edclientKeyPress
    end
    object chcode: TCheckBox
      Left = 5
      Top = 70
      Width = 74
      Height = 17
      Caption = #21333#21495#33539#22260
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
    object edcode: TEdit
      Left = 85
      Top = 68
      Width = 64
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      NumbersOnly = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 7
      OnChange = edcodeChange
    end
    object DBGrid1: TDBGrid
      Left = 5
      Top = 99
      Width = 740
      Height = 330
      Ctl3D = False
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = PopupMenu1
      TabOrder = 8
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      OnKeyPress = DBGrid1KeyPress
      Columns = <
        item
          Expanded = False
          FieldName = 'xuhao'
          Title.Alignment = taCenter
          Title.Caption = #24207#21495
          Width = 30
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'clientname'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'operator'
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Id'
          Visible = False
        end>
    end
    object Button1: TButton
      Left = 490
      Top = 66
      Width = 75
      Height = 25
      Caption = #26597#35810
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 569
      Top = 66
      Width = 75
      Height = 25
      Caption = #36864#20986
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 10
      OnClick = Button2Click
    end
    object chinorder: TCheckBox
      Left = 490
      Top = 41
      Width = 97
      Height = 17
      Caption = #20869#37096#35746#21333
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 11
      Visible = False
    end
    object cbclient: TComboBox
      Left = 156
      Top = 37
      Width = 323
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ItemHeight = 17
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 12
      OnChange = cbclientChange
      OnClick = cbclientClick
    end
    object cbshenghe: TCheckBox
      Left = 594
      Top = 41
      Width = 73
      Height = 17
      Caption = #24453#23457#26680
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 13
      Visible = False
    end
    object cbweisheng: TCheckBox
      Left = 678
      Top = 41
      Width = 73
      Height = 17
      Caption = #24050#23457#26680
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 14
      Visible = False
    end
    object editcode2: TEdit
      Left = 174
      Top = 68
      Width = 64
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      NumbersOnly = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 15
      OnChange = edcodeChange
    end
    object cbfahuofashi: TComboBox
      Left = 565
      Top = 7
      Width = 180
      Height = 25
      BevelKind = bkFlat
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ItemHeight = 17
      ItemIndex = 0
      ParentFont = False
      TabOrder = 16
      Text = #31038#30452#21457
      Visible = False
      OnChange = cbfahuofashiChange
      Items.Strings = (
        #31038#30452#21457
        #28100#36716#21457)
    end
    object checkfahuofashi: TCheckBox
      Left = 489
      Top = 11
      Width = 74
      Height = 17
      Caption = #21457#36135#26041#24335
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 17
      Visible = False
    end
    object cbchao: TCheckBox
      Left = 247
      Top = 70
      Width = 58
      Height = 17
      Caption = #25805#20316#21592
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 18
    end
    object cboperator: TComboBox
      Left = 330
      Top = 68
      Width = 149
      Height = 25
      BevelKind = bkFlat
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ItemHeight = 17
      ParentFont = False
      TabOrder = 19
      OnChange = cboperatorChange
    end
    object editorderbk: TEdit
      Left = 565
      Top = 8
      Width = 180
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      NumbersOnly = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 20
      Visible = False
      OnChange = editorderbkChange
    end
    object cborderbk: TCheckBox
      Left = 489
      Top = 11
      Width = 74
      Height = 17
      Caption = #22791#27880
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 21
      Visible = False
    end
  end
  object fcon: TADOConnection
    Left = 192
    Top = 192
  end
  object ds: TDataSource
    DataSet = query
    Left = 336
    Top = 184
  end
  object query: TADOQuery
    Parameters = <>
    Left = 376
    Top = 288
  end
  object PopupMenu1: TPopupMenu
    Left = 288
    Top = 288
    object A1: TMenuItem
      Caption = #20840#36873'(&A)'
      OnClick = A1Click
    end
    object P1: TMenuItem
      Caption = #25171#21360'(&P)'
      OnClick = P1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object N2: TMenuItem
      Caption = #26356#26032#22791#27880
      OnClick = N2Click
    end
  end
end
