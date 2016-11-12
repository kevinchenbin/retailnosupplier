object frmpsquery: Tfrmpsquery
  Left = 0
  Top = 0
  Caption = #37197#36865#26597#21333
  ClientHeight = 474
  ClientWidth = 435
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
    Width = 435
    Height = 474
    Align = alClient
    BevelInner = bvLowered
    ParentBackground = False
    TabOrder = 0
    object dtpstart: TDateTimePicker
      Left = 85
      Top = 5
      Width = 116
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 0
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 12
      Top = 9
      Width = 74
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 1
    end
    object dtpend: TDateTimePicker
      Left = 306
      Top = 5
      Width = 116
      Height = 25
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 2
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 231
      Top = 9
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 3
    end
    object choutstorage: TCheckBox
      Left = 12
      Top = 37
      Width = 65
      Height = 17
      Caption = #35843#20986#24215
      TabOrder = 4
    end
    object chcode: TCheckBox
      Left = 12
      Top = 101
      Width = 67
      Height = 17
      Caption = #21333#21495
      TabOrder = 5
    end
    object edcode: TEdit
      Left = 85
      Top = 98
      Width = 337
      Height = 25
      NumbersOnly = True
      TabOrder = 6
      OnChange = edcodeChange
      OnKeyPress = edcodeKeyPress
    end
    object DBGrid1: TDBGrid
      Left = 2
      Top = 164
      Width = 431
      Height = 308
      Align = alBottom
      Ctl3D = False
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 7
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'stgnameout'
          Title.Alignment = taCenter
          Title.Caption = #35843#20986#24215
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ZNDiaoNtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 110
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
          FieldName = 'stgnamein'
          Title.Alignment = taCenter
          Title.Caption = #35843#20837#24215
          Width = 120
          Visible = True
        end>
    end
    object Button1: TButton
      Left = 253
      Top = 129
      Width = 75
      Height = 25
      Caption = #26597#35810
      TabOrder = 8
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 347
      Top = 129
      Width = 75
      Height = 25
      Caption = #36864#20986
      TabOrder = 9
      OnClick = Button2Click
    end
    object cboutstorage: TComboBox
      Left = 85
      Top = 35
      Width = 116
      Height = 25
      ItemHeight = 17
      TabOrder = 10
      OnChange = cboutstorageChange
    end
    object chinstorage: TCheckBox
      Left = 231
      Top = 37
      Width = 65
      Height = 17
      Caption = #35843#20837#24215
      TabOrder = 11
    end
    object cbinstorage: TComboBox
      Left = 306
      Top = 35
      Width = 116
      Height = 25
      ItemHeight = 17
      TabOrder = 12
      OnChange = cbinstorageChange
    end
    object ckstate: TCheckBox
      Left = 12
      Top = 68
      Width = 65
      Height = 17
      Caption = #29366#24577
      TabOrder = 13
    end
    object cbstate: TComboBox
      Left = 85
      Top = 66
      Width = 337
      Height = 25
      ItemHeight = 17
      TabOrder = 14
      OnChange = cbstateChange
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 408
    Top = 208
  end
  object query: TADOQuery
    Parameters = <>
    Left = 224
    Top = 208
  end
  object fcon: TADOConnection
    Left = 464
    Top = 128
  end
end
